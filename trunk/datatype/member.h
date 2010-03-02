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

	//Member methods
	bool owesMoney();
	bool isMovedIn();
	void addDependant(Dependant dependant);	

	//Acessor methods
	string getTelephoneNumber() {return telephoneNumber;}
	double getMoneyOwed() {retrun moneyOwed;}
	bool   sharedTelephone() {return shareTelephone;}
	bool   checkMarked()	{return isMarked;}
	string firstName() {return firstName;}
	string lastName()  {return lastName;}

	//Modifiers
	void setTelephoneNumber(string newNumber);
	void setMoneyOwed(double money);
	void setSharedTelephone(bool share);
	void setMarked(bool mark);
	void setFirstName(string newFirstName);
	void setLastName(string newLastName);

private:
	string telephoneNumber;
	double moneyOwed = 0.0;
	bool shareTelephone = true;
	bool isMarked = false;
	string firstName;
	string lastName;
};

#endif // MEMBER_H
