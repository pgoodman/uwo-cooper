
#include "member.h"

/*Member::Member()
{
    moneyOwed = 0.0;
    shareTelephone = true;
    isMarked = false;
}*/


/**
 * Private Constructor, used for loading a member from the database.
 */
Member::Member(string fullName, double newMoneyOwed,
               string phoneNum, bool sharePhone, bool mark,
               string uName, string pass, bool hasCommittee, int userId)
{
    full_name = fullName;
	money_owed = newMoneyOwed;
	share_telephone = sharePhone;
	is_marked = mark;
	telephone_num = phoneNum;
	password = pass;
	user_name = uName;
	has_committee = hasCommittee;
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
string Member::getUserName(void) {
    return user_name;
}

#if 0

void Member::setTelephoneNumber(string newNumber)
{
	telephoneNumber = newNumber;
}

void Member::setMoneyOwed(double money)
{
	moneyOwed = money;
}

void Member::setSharedTelephone(bool share)
{
	shareTelephone = share;
}

void Member::setMarked(bool mark)
{
	isMarked = mark;
}

#endif

/**
 * Create a member.
 */
User *Member::create(string full_name, string telephone,
                     const bool share_telephone, string user_name,
                     string password, const time_t move_in_time) {
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
        "telephone=?,move_in_time=?,is_marked=?,committee_id=? WHERE id=? "
        "AND is_coordinator=0"
    );
    q << full_name << user_name << password << share_telephone
      << telephone_num << move_in_time << is_marked;

    if(0 != committee) {
        q << committee->getId();
    } else {
        q << NULL;
    }
    q << id;

    if(!q.exec() || 0 == q.numRowsAffected()) {
        CooperDB::queryError("Unable to Update Member Information.", q);
    }
}

/**
 * Load a user from the database given the user's id. Will return NULL if the
 * user doesn't exist.
 */
User *Member::load(const int id) {
    if(User::remembered(id)) {
        return User::recall(id);
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
User *Member::load(string &user_name, string &pass) {
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
User *Member::load(QSqlQuery &q, const bool checked_id) {
    q.first();
    if(!q.isValid()) {
        return NULL;
    }

    if(qcol<bool>(q, "is_coordinator")) {
        q.finish();
        return Coordinator::load(); // will already be loaded
    }

    int id(qcol<int>(q, "id"));

    // make sure we don't have two objects around for the same user
    if(!checked_id) {
        if(User::remembered(id)) {
            q.finish();
            return User::recall(id);
        }
    }

    // load the member as an object to be used
    User *u = new Member(
        qcol<string>(q, "full_name"),
        qcol<double>(q, "money_owed"),
        qcol<string>(q, "telephone"),
        qcol<bool>(q, "share_telephone"),
        qcol<bool>(q, "is_marked"),
        qcol<string>(q, "name"),
        qcol<string>(q, "password"),
        qcol<int>(q, "committee_id") != 0, // has committee?
        id
    );

    q.finish();
    User::remember(id, u);
    return u;
}

/**
 * Find a sequence of members.
 */
pair<Member::iterator, Member::iterator> Member::find() {
    QSqlQuery count = QSqlQuery(
        "SELECT COUNT(id) AS c FROM user WHERE is_coordinator=0 LIMIT 1"
    );
    int size((count.next() && count.isValid()) ? qcol<int>(count, "c") : 0);
    count.finish();

    QSqlQuery *query = new QSqlQuery(
        "SELECT id FROM user WHERE is_coordinator=0"
    );

    query->next();
    iterator start(query, size, 0);
    iterator end(query, size, size + 1);
    return make_pair(start, end);
}
