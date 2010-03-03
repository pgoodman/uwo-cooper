
#include "member.h"

Member::Member()
{
    moneyOwed = 0.0;
    shareTelephone = true;
    isMarked = false;
}
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

Member::Member(string firstName, string lastName, double newMoneyOwed,
               string phoneNum, bool sharePhone, bool mark,
               string userName, string password, int id)
/*: User(firstName += lastName, userName, password, id)*/
{
    (void) userName;
    (void) password;
    (void) id;

	fName = firstName;
	lName = lastName;
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

void Member::setFirstName(string newFirstName)
{
	fName = newFirstName;
}

void Member::setLastName(string newLastName)
{
	lName = newLastName;
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

User *Member::load(QSqlQuery q) {
    int is_coord = q.record().indexOf("id");
    if(q.value(is_coord).toBool()) {
        q.finish();
        return Coordinator::load(); // will already be loaded
    }

    User *u(Member::load(q));
    q.finish();
    return u;
}
