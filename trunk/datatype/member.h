#ifndef MEMBER_H
#define MEMBER_H

#include <string>

#include <QVariant>
#include <QSqlRecord>

#include "datatype/user.h"
#include "datatype/coordinator.h"
#include "datatype/dependant.h"

using namespace std;

class Member : public User {

    friend class User;

public:
	//Constructors


	//Member methods
	bool owesMoney();
	bool isMovedIn();
	void addDependant(Dependant dependant);	

	//Acessor methods
	string getTelephoneNumber() {return telephoneNumber;}
	double getMoneyOwed() {return moneyOwed;}
	bool   sharedTelephone() {return shareTelephone;}
	bool   checkMarked() {return isMarked;}
	string firstName() {return fName;}
	string lastName()  {return lName;}

	//Modifiers
	void setTelephoneNumber(string newNumber);
	void setMoneyOwed(double money);
	void setSharedTelephone(bool share);
	void setMarked(bool mark);
	void setFirstName(string newFirstName);
	void setLastName(string newLastName);

	static User *load(const int id);
    static User *load(string &uname, string &pass);

private:

    static User *load(QSqlQuery q);

	string telephoneNumber;
	double moneyOwed;
	bool shareTelephone;
	bool isMarked;
	string fName;
	string lName;
	string userName;


	Member();
    //Member(string firstName, string lastName, string phoneNum, string userName, string password, int id);
    Member(string firstName, string lastName, double newMoneyOwed,
           string phoneNum, bool sharePhone, bool mark, string userName,
           string password, int id);
};

#endif // MEMBER_H
