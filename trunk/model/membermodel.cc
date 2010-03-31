
#include "model/membermodel.h"

const char *MemberModel::table_name("user");

/**
 * Private Constructor, used for loading a member from the database.
 */
MemberModel::MemberModel(const int id,
               const int committeeId,
               const int unitId,
               const bool sharePhone,
               const bool isMarked,
               const bool hadCommittee,
               const double moneyOwed,
               const QDateTime moveInTime,
               QString phoneNum,
               QString userName,
               QString firstName,
               QString lastName,
               QString addr,
               QString pass)

 : UserModel(false, pass), IModel<MemberModel, select_from_table_tag>(id),
   committee_id(committeeId),
   unit_id(unitId), share_telephone(sharePhone), is_marked(isMarked),
   had_committee(hadCommittee), money_owed(moneyOwed),
   move_in_time(moveInTime), telephone_num(phoneNum),
   user_name(userName), first_name(firstName), last_name(lastName),
   address(addr)
{ }

/**
 * Destructor.
 */
MemberModel::~MemberModel(void) { }

/**
 * Check whether or not a coodinator has a permission.
 */
bool MemberModel::hasPermission(const PermissionModelSet p) {
    if(0 == committee_id) {
        return (EDIT_SELF_PASS == p);
    }
    CommitteeModel *c = findCommittee();
    if(0 == c) {
        committee_id = 0;
        return false;
    }
    return 0 != (p & c->getPermissions(id));
}

/**
 * Remove a member from the database iff they are already marked deleted.
 */
bool MemberModel::remove(void) {
    if(isMarkedDeleted()) {
        QSqlQuery q;
        q.prepare("DELETE FROM dependant WHERE member_id=?");
        q << id;
        q.exec();

        // TODO: clean up any committee stuff

        return IModel<MemberModel,select_from_table_tag>::remove();
    }

    return false;
}

/**
 * Get a member's committee.
 */
CommitteeModel *MemberModel::findCommittee(void) {
    if(0 == committee_id) {
        return 0;
    }
    committee = CommitteeModel::findById(committee_id);
    return committee;
}

/**
 * Get this user's login name.
 */
QString MemberModel::getUserName(void) {
    return user_name;
}

QString MemberModel::getTelephoneNum(){
    return telephone_num;
}
void MemberModel::setTelephoneNumber(QString newNumber)
{
	telephone_num = newNumber;
}

double MemberModel::getMoneyOwed(){
    return money_owed;
}

void MemberModel::setMoneyOwed(double money)
{
	money_owed = money;
}

bool MemberModel::isTelephoneShared(){
    return share_telephone;
}
void MemberModel::setSharedTelephone(bool share)
{
	share_telephone = share;
}

bool MemberModel::isMarkedDeleted() {
    return is_marked;
}
void MemberModel::markDeleted(bool mark) {
	is_marked = mark;
}

QString MemberModel::toString(void) {
    stringstream ss;
    if(!first_name.isEmpty()) {
        ss << first_name.toStdString() << " ";
    }
    ss << last_name.toStdString();
    if(is_marked) {
        ss << " [marked]";
    }
    if(first_name.isEmpty()) {
        ss << " [incomplete]";
    }
    return QString(ss.str().c_str());
}

void MemberModel::setFullName(QString firstName, QString lastName)
{
    first_name = firstName;
    last_name = lastName;
}

QString MemberModel::getFirstName(){
    return first_name;
}

void MemberModel::setFirstName(QString firstName){
    first_name=firstName;
}

QString MemberModel::getLastName(){
    return last_name;
}
void MemberModel::setLastName(QString lastName){
    last_name=lastName;
}

UnitModel *MemberModel::findUnit(void) {
    if(0 == unit_id) {
        return 0;
    }
    unit = UnitModel::findById(unit_id);
    return unit;
}

void MemberModel::setUnit(UnitModel *unit_to_set) {
    unit_id = unit_to_set->id;
    address = unit_to_set->address;
    unit = unit_to_set;
}

QString MemberModel::getAddress(){
    return address;
}
void MemberModel::setAddress(QString addr){
    address=addr;
}

void MemberModel::setCommittee(CommitteeModel *comm) {
    if(0 == comm) {
        committee_id = 0;
        committee = 0;
    } else {
        committee_id = comm->id;
        committee = comm;
    }
}

QString MemberModel::getLoginName(){
    return user_name;
}

void MemberModel::setLoginName(QString loginName){
    user_name = loginName;
}

QDateTime MemberModel::getMoveInTime(){
    return move_in_time;
}

void MemberModel::setMoveInTime(QDateTime mvTime){
    move_in_time = mvTime;
}

/**
 * Create a member.
 */
MemberModel *MemberModel::create(const bool sharePhone,
                       QDateTime moveInTime,
                       QString phoneNum,
                       QString userName,
                       QString firstName,
                       QString lastName,
                       QString addr,
                       QString pass,
                       CommitteeModel *committee,
                       UnitModel *unit,
                       const bool unit_will_be_empty) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO user (first_name,last_name,name,password,share_telephone,"
        "telephone, move_in_time, unit_id, address,committee_id,had_committee) "
        "VALUES (?,?,?,?,?,?,?,?,?,?,?)"
    );
    const int committee_id((0 == committee) ? 0 : committee->id);
    const int unit_id((0 == unit) ? 0 : unit->id);
    const bool had_committee(0 != committee);

    q << firstName << lastName << userName << pass << sharePhone
      << phoneNum << moveInTime << unit_id << addr << committee_id
      << had_committee;

    if(!q.exec()) {
        return 0;
    }

    // add this member to the the number of tenants for this unit.
    if(0 != unit) {
        unit->updateNumTenants(1);

        QString *task_desc(new QString);
        QTextStream ss(task_desc);
        ss << "Member Name: " << firstName << " " << lastName << "\n";
        if(sharePhone) {
            ss << "Telephone Number: " << phoneNum << "\n";
        }
        ss << "Unit Number: " << unit->id << "\n";
        ss << "Move-in Date: " << moveInTime.toString("MMMM d, yyyy") << "\n";

        QDateTime in_30_days(moveInTime);
        in_30_days = in_30_days.addDays(30);

        // If a unit has a new member moving into it, and it will be empty when
        // the new member moves into it, then a Move-In Inspection task must be
        // added to the task list of the Inspection Committee.
        //
        // The description for the task must include the name(s) of the member
        // moving in, the tele-phone number(s) of the member(s) if not
        // confidential, and the number of the unit they are moving into. The
        // deadline for the inspection must be one month after the memberÕs
        // move-in date.
        if(unit_will_be_empty) {
            CommitteeModel *ic(CommitteeModel::findById(
                CommitteeModel::INSPECTIONS_COMMITTEE_ID
            ));
            ic->addTask(QString("Move-in Event"), *task_desc, in_30_days);
        }

        // Every New Member event must add an Orientation task to the task
        // list of the Education committee. The description for the task
        // must include the name of the member, their telephone number if
        // not confidential, the number of the unit they are moving into,
        // and their move-in date.
        CommitteeModel *ec(CommitteeModel::findById(
            CommitteeModel::EDUCATION_COMMITTEE_ID
        ));
        ec->addTask(QString("Orientation Event"), *task_desc, in_30_days);

        delete task_desc;
    }

    return findById(q.lastInsertId().toInt());
}

/**
 * Create an incomplete member profile.
 */
MemberModel *MemberModel::createIncomplete(QString last_name, UnitModel *unit) {
    int unit_id(0 == unit ? 0 : unit->id);
    QSqlQuery q;
    q.prepare("INSERT INTO user (last_name,unit_id) VALUES (?,?)");
    q << last_name << unit_id;
    if(!q.exec()) {
        return 0;
    }
    return findById(q.lastInsertId().toInt());
}

/**
 * Update the user's info in the db.
 */
bool MemberModel::save(void) {
    QSqlQuery q;
    q.prepare(
        "UPDATE user SET first_name=?,last_name=?,name=?,password=?,"
        "share_telephone=?,telephone=?,move_in_time=?,unit_id=?,address=?,"
        "is_marked=?,committee_id=?,money_owed=?,had_committee=? "
        "WHERE id=? AND is_coordinator=0"
    );

    bool did_have_committee(had_committee || 0 != committee);

    q << first_name << last_name << user_name << password << share_telephone
      << telephone_num << move_in_time << unit_id << address << is_marked
      << committee_id << money_owed << did_have_committee << id;

    return q.exec();
}

/**
 * Load a user from the database given the user's username and password. Will
 * return NULL if the user can't be loaded.
 */
MemberModel *MemberModel::findByLoginInfo(QString user_name, QString pass) {
    QSqlQuery q;
    q.prepare("SELECT * FROM user WHERE name=? AND password=?");
    q << user_name << pass;
    if(!q.exec() || !q.first()) {
        return 0;
    }
    return load(q, qcol<int>(q, "id"));
}

/**
 * Load a member (or coordinator) from the database given the query that
 * fetched that user.
 */
MemberModel *MemberModel::load(QSqlQuery &q, const int id) {
    if(qcol<bool>(q, "is_coordinator")) {
        q.finish();
        return 0;
    }

    // load the member as an object to be used
    MemberModel *u = new MemberModel(
        id,
        qcol<int>(q, "committee_id"),
        qcol<int>(q, "unit_id"),
        qcol<bool>(q, "share_telephone"),
        qcol<bool>(q, "is_marked"),
        qcol<bool>(q, "had_committee"),
        qcol<double>(q, "money_owed"),
        qcol<QDateTime>(q, "move_in_time"),
        qcol<QString>(q, "telephone"),
        qcol<QString>(q, "name"),
        qcol<QString>(q, "first_name"),
        qcol<QString>(q, "last_name"),
        qcol<QString>(q, "address"),
        qcol<QString>(q, "password")
    );
    return u;
}

/**
 * Find a sequence of members, overwrites IModel<MemberModel>::findAll().
 */
MemberModel::iterator_range MemberModel::findAll(void) {
    return Database::selectAll<MemberModel>("user", "is_coordinator=0");
}
MemberModel::iterator_range MemberModel::findAll(const char *cond) {
    stringstream ss;
    ss << "is_coordinator=0 AND " << cond;
    return Database::selectAll<MemberModel>("user", ss.str().c_str());
}

/**
 * Figure out if a member was ever assigned to a committee. This is important
 * as chair of the education committee is only allowed to assign the committee
 * to a new member who has never had their committee assigned.
 */
bool MemberModel::wasAssignedCommittee(void) {
    return had_committee;
}

/**
 * Get all of a member's dependants.
 */
DependantModel::iterator_range MemberModel::findDependants(void) {
    stringstream ss;
    ss << "member_id=" << id;
    return Database::selectAll<DependantModel>("dependant", ss.str().c_str());
}
/**
  * Get member's role at committee, Chair, Secretary or Member
  */
QString MemberModel::getRoleAtCommittee() {
    CommitteeModel *c = this->findCommittee();
    return c->getMemberRoleByID(member_id);
}

/**
 * Add a dependant.
 */
DependantModel *MemberModel::addDependant(QString name, QDateTime bday) {
    return DependantModel::create(name, bday, id);
}
