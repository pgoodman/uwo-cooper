
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
   money_owed(moneyOwed), move_in_time(moveInTime), telephone_num(phoneNum),
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
bool MemberModel::hasPermission(const PermissionModel p) {
    if(0 == committee_id) {
        return (EDIT_SELF_PASS == p);
    }
    CommitteeModel *c = getCommittee();
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
        return IModel<MemberModel,select_from_table_tag>::remove();
    }
    return false;
}

/**
 * Get a member's committee.
 */
CommitteeModel *MemberModel::getCommittee(void) {
    if(0 == committee_id) {
        return 0;
    }
//    else if(0 != committee) {
//        return committee;
//    }
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

UnitModel *MemberModel::getUnit(void) {
    if(0 == unit_id) {
        return 0;
    }
    unit = UnitModel::findById(unit_id);
    return unit;
}

QString MemberModel::getUnitNo(){
    QString uid;
    uid.setNum(unit_id);
    return uid;
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

int MemberModel::getCommitteeId(){
    return committee_id;
}

void MemberModel::setCommittee(CommitteeModel *comm) {
    committee_id = comm->id;
    committee = comm;
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
                       UnitModel *unit) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO user (first_name,last_name,name,password,share_telephone,"
        "telephone, move_in_time, unit_id, address, committee_id) VALUES "
        "(?,?,?,?,?,?,?,?,?,?)"
    );
    const int committee_id = (0 == committee) ? 0 : committee->id;
    const int unit_id = (0 == unit) ? 0 : unit->id;

    q << firstName << lastName << userName << pass << sharePhone
      << phoneNum << moveInTime << unit_id << addr << committee_id;

    if(!q.exec()) {
        return 0;
    }

    // add this member to the the number of tenants for this unit.
    if(0 != unit) {
        bool unit_was_empty(unit->isEmpty());
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
        in_30_days.addDays(30);

        // If a unit has a new member moving into it, and it will be empty when
        // the new member moves into it, then a Move-In Inspection task must be
        // added to the task list of the Inspection Committee.
        //
        // The description for the task must include the name(s) of the member
        // moving in, the tele-phone number(s) of the member(s) if not
        // confidential, and the number of the unit they are moving into. The
        // deadline for the inspection must be one month after the memberÕs
        // move-in date.
        if(unit_was_empty) {
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
        "is_marked=?,committee_id=?,money_owed=? "
        "WHERE id=? AND is_coordinator=0"
    );
    q << first_name << last_name << user_name << password << share_telephone
      << telephone_num << move_in_time << unit_id << address << is_marked
      << committee_id << money_owed << id;

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


void MemberModel::setCommitteeID(int cid){
    committee_id = cid;
    //committee = CommitteeModel::findById(cid);
}
