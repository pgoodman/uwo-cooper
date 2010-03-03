
#include "member.h"

/*Member::Member()
{
    moneyOwed = 0.0;
    shareTelephone = true;
    isMarked = false;
}*/

#if 0
/**
 * Public constructor, creates a member that isn't saved.
 */
Member::Member(string fullName, string phoneNum, string uName, string password)
{
    (void) password;
    (void) id;

	full_name = fullName;
	telephoneNumber = phoneNum;
	moneyOwed = 0.0;
    shareTelephone = true;
    isMarked = false;
    userName = uName;
    isSaved = false; // not in the db
}
#endif

/**
 * Private Constructor, used for loading a member from the database.
 */
Member::Member(string fullName, double newMoneyOwed,
               string phoneNum, bool sharePhone, bool mark,
               string uName, string pass, Committee *comm, int userId)
{
    full_name = fullName;
	moneyOwed = newMoneyOwed;
	shareTelephone = sharePhone;
	isMarked = mark;
	telephoneNumber = phoneNum;
	password = pass;
	userName = uName;
	committee = comm;
	id = userId;
}

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

string Member::getUserName(void) {
    return userName;
}

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
    q.bindValue(0, QVariant(full_name.c_str()));
    q.bindValue(1, QVariant(user_name.c_str()));
    q.bindValue(2, QVariant(password.c_str()));
    q.bindValue(3, QVariant(share_telephone));
    q.bindValue(4, QVariant(telephone.c_str()));
    q.bindValue(5, QVariant(static_cast<unsigned int>(move_in_time)));

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
        "telephone=?,move_in_time=?,is_marked=?,committee_id=? WHERE id=?"
    );
    q.bindValue(0, QVariant(full_name.c_str()));
    q.bindValue(1, QVariant(userName.c_str()));
    q.bindValue(2, QVariant(password.c_str()));
    q.bindValue(3, QVariant(shareTelephone));
    q.bindValue(4, QVariant(telephoneNumber.c_str()));
    q.bindValue(5, QVariant(static_cast<unsigned int>(moveInTime)));
    q.bindValue(6, QVariant(isMarked));

    if(0 != committee) {
        q.bindValue(7, QVariant(committee->getId()));
    } else {
        q.bindValue(7, QVariant(0));
    }

    q.bindValue(8, QVariant(id));
    if(!q.exec()) {
        CooperDB::queryError("Unable to Update Member Information.", q);
    }
}

/**
 * Load a user from the database given the user's id. Will return NULL if the
 * user doesn't exist.
 */
User *Member::load(const int id) {
    if(0 != users[id]) {
        return users[id];
    }

    QSqlQuery q;
    q.prepare("SELECT * FROM user WHERE id=?");
    q.bindValue(0, QVariant(id));
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
    q.bindValue(0, QVariant(user_name.c_str()));
    q.bindValue(1, QVariant(pass.c_str()));
    if(!q.exec()) {
        CooperDB::queryError("Unable to load Member by user/pass", q);
    }
    return load(q, false);
}

/**
 * Quickly get the variant from the query given a column name.
 */
static QVariant at(QSqlQuery &q, const char *index) {
    return q.value(q.record().indexOf(index));
}

/**
 * Load a member (or coordinator) from the database given the query that
 * fetched that user.
 */
User *Member::load(QSqlQuery &q, const bool checked_id) {

    if(!q.isValid()) {
        return NULL;
    }

    if(at(q, "is_coord").toBool()) {
        q.finish();
        return Coordinator::load(); // will already be loaded
    }

    int id(at(q, "id").toInt());

    // make sure we don't have two objects around for the same user
    if(!checked_id) {
        if(0 != users[id]) {
            q.finish();
            return users[id];
        }
    }

    // load the member as an object to be used
    User *u = new Member(
        at(q, "full_name").toString().toStdString(),
        at(q, "money_owed").toDouble(),
        at(q, "telephone").toString().toStdString(),
        at(q, "share_telephone").toBool(),
        at(q, "is_marked").toBool(),
        at(q, "name").toString().toStdString(),
        at(q, "password").toString().toStdString(),
        Committee::load(at(q, "committee_id").toInt()),
        id
    );

    q.finish();
    users.insert(users.begin() + id, u);
    return u;
}
