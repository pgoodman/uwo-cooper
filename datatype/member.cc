#include "member.h"

Member::Member()
{
    moneyOwed = 0.0;
    shareTelephone = true;
    isMarked = false;
}

Member::Member(string firstName, string lastName, string phoneNum,
			   string userName, string password, int id)
:
User(firstName += lastName, userName, password, id)
{
	fName = firstName;
	lName = lastName;
	telephoneNumber = phoneNum;
	moneyOwed = 0.0;
    shareTelephone = true;
    isMarked = false;
}

Member::Member(string firstName, string lastName, double newMoneyOwed, string phoneNum, 
			   bool sharePhone, bool mark, std::string userName, std::string password, int id) 
: 
User(firstName += lastName, userName, password, id)
{
	fName = firstName;
	lName = lastName;
	moneyOwed = newMoneyOwed;
	shareTelephone = sharePhone;
	isMarked = mark;
	telephoneNumber = phoneNum;
}
