#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include "user.h"
#include "dependant.h"

using namespace std;

class Member : public User{

public:
	//Constructors
	Member();
	Member(string newFirstName, string newLastName);
	Member(string newFirstName, string newLastName, double newMoneyOwed, 
		bool sharePhone, bool mark);

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

private:
	string telephoneNumber;
	double moneyOwed;
	bool shareTelephone;
	bool isMarked;
	string fName;
	string lName;
};

#endif // MEMBER_H
