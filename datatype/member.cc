
#include "member.h"

/*Member::Member()
{
    moneyOwed = 0.0;
    shareTelephone = true;
    isMarked = false;
}*/
#if 0
Member::Member(string firstName, string lastName, string phoneNum,
			   string uName, string password, int id)
/*: User(firstName += lastName, userName, password, id)*/
{
    (void) password;
    (void) id;

	fName = firstName;
	lName = lastName;
	telephoneNumber = phoneNum;
	moneyOwed = 0.0;
    shareTelephone = true;
    isMarked = false;

    userName = uName;
}
#endif

Member::Member(string fullName, double newMoneyOwed,
               string phoneNum, bool sharePhone, bool mark,
               string userName, string password, int id)
{
    (void) userName;
    (void) password;
    (void) id;

	_fullName = fullName;
	moneyOwed = newMoneyOwed;
	shareTelephone = sharePhone;
	isMarked = mark;
	telephoneNumber = phoneNum;
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

void Member::setFullName(string full_name)
{
	_fullName = full_name;
}

string Member::getUserName(void) {
    return userName;
}

User *Member::load(const int id) {
    if(0 != users[id]) {
        return users[id];
    }

    QSqlQuery q;
    q.prepare("SELECT * FROM user WHERE id=?");
    q.bindValue(0, QVariant(id));
    q.exec();
    return load(q);
}

User *Member::load(string &user_name, string &pass) {
    QSqlQuery q;
    q.prepare("SELECT * FROM user WHERE name=? AND password=?");
    q.bindValue(0, QVariant(user_name.c_str()));
    q.bindValue(1, QVariant(pass.c_str()));
    q.exec();
    return load(q);
}

static QVariant at(QSqlQuery &q, const char *index) {
    return q.value(q.record().indexOf(index));
}

User *Member::load(QSqlQuery &q) {
    if(!q.isValid()) {
        return NULL;
    }

    if(at(q, "is_coord").toBool()) {
        q.finish();
        return Coordinator::load(); // will already be loaded
    }

    User *u = new Member(
        at(q, "full_name").toString().toStdString(),
        at(q, "money_owed").toDouble(),
        at(q, "telephone").toString().toStdString(),
        at(q, "share_telephone").toBool(),
        at(q, "is_marked").toBool(),
        at(q, "name").toString().toStdString(),
        at(q, "password").toString().toStdString(),
        at(q, "id").toInt()
    );

    q.finish();
    return u;
}
