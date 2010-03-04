
#include "member.h"

/**
 * Private Constructor, used for loading a member from the database.
 */
Member::Member(QString fullName, double newMoneyOwed,
               QString phoneNum, bool sharePhone, bool mark,
               QString uName, QString pass, int committeeId, int userId)
{
    full_name = fullName;
	money_owed = newMoneyOwed;
	share_telephone = sharePhone;
	is_marked = mark;
	telephone_num = phoneNum;
	password = pass;
	user_name = uName;
	committee_id = committeeId;
	id = userId;
}

/**
 * Check whether or not a coodinator has a permission.
 */
bool Member::hasPermission(const Permission p) {
    (void) p;
    return true;
}

/**
 * Get this user's login name.
 */
QString Member::getUserName(void) {
    return user_name;
}

void Member::setTelephoneNumber(QString newNumber)
{
	telephone_num = newNumber;
}

void Member::setMoneyOwed(double money)
{
	money_owed = money;
}

void Member::setSharedTelephone(bool share)
{
	share_telephone = share;
}

void Member::setMarked(bool mark)
{
	is_marked = mark;
}

QString Member::getFullName(void) {
    return full_name;
}

void Member::setFullName(QString fullName)
{
    full_name = fullName;
}

/**
 * Create a member.
 */
Member *Member::create(QString full_name, QString telephone,
                     const bool share_telephone, QString user_name,
                     QString password, const time_t move_in_time) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO user (full_name, name, password, share_telephone, "
        "telephone, move_in_time) VALUES (?, ?, ?, ?, ?, ?)"
    );

    q << full_name << user_name << password << share_telephone
      << telephone << move_in_time;

    if(!q.exec()) {
        CooperDB::queryError("Unable to Create Member", q);
    }

    return load(q.lastInsertId().toInt());
}

/**
 * Update the user's info in the db.
 */
void Member::save(void) {
    QSqlQuery q;
    q.prepare(
        "UPDATE user SET full_name=?,name=?,password=?,share_telephone=?,"
        "telephone=?,move_in_time=?,is_marked=?,committee_id=?,money_owed=? "
        "WHERE id=? AND is_coordinator=0"
    );
    q << full_name << user_name << password << share_telephone
      << telephone_num << move_in_time << is_marked << committee_id
      << money_owed << id;

    if(!q.exec() || 0 == q.numRowsAffected()) {
        CooperDB::queryError("Unable to Update Member Information.", q);
    }
}

/**
 * Load a user from the database given the user's id. Will return NULL if the
 * user doesn't exist.
 */
Member *Member::load(const int id) {
    if(User::remembered(id)) {
        User *u(User::recall(id));
        if(u == Coordinator::load()) {
            return 0;
        }
        return static_cast<Member *>(u);
    }

    QSqlQuery q;
    q.prepare("SELECT * FROM user WHERE id=?");
    q << id;
    if(!q.exec()) {
        CooperDB::queryError("Unable to load Member by ID", q);
    }
    return load(q);
}

/**
 * Load a user from the database given the user's username and password. Will
 * return NULL if the user can't be loaded.
 */
Member *Member::load(QString &user_name, QString &pass) {
    QSqlQuery q;
    q.prepare("SELECT * FROM user WHERE name=? AND password=?");
    q << user_name << pass;
    if(!q.exec()) {
        CooperDB::queryError("Unable to load Member by user/pass", q);
    }
    return load(q, false);
}

/**
 * Load a member (or coordinator) from the database given the query that
 * fetched that user.
 */
Member *Member::load(QSqlQuery &q, const bool checked_id) {
    q.first();
    if(!q.isValid()) {
        return 0;
    }

    if(qcol<bool>(q, "is_coordinator")) {
        q.finish();
        //return Coordinator::load(); // will already be loaded
        return 0;
    }

    int id(qcol<int>(q, "id"));

    // make sure we don't have two objects around for the same user
    if(!checked_id) {
        if(User::remembered(id)) {
            q.finish();
            return static_cast<Member *>(User::recall(id));
        }
    }

    // load the member as an object to be used
    Member *u = new Member(
        qcol<QString>(q, "full_name"),
        qcol<double>(q, "money_owed"),
        qcol<QString>(q, "telephone"),
        qcol<bool>(q, "share_telephone"),
        qcol<bool>(q, "is_marked"),
        qcol<QString>(q, "name"),
        qcol<QString>(q, "password"),
        qcol<int>(q, "committee_id"),
        id
    );

    q.finish();
    User::remember(id, u);
    return u;
}

/**
 * Find a sequence of members.
 */
pair<Member::iterator, Member::iterator> Member::findAll() {
    return CooperDB::selectAll<Member,Member>("user", "is_coordinator=0");
}