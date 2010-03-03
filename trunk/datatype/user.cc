#include <string>
#include "user.h"

using namespace std;

User::User()
{
}

User::User(string newName, string newUserName, string newPassword, int newID)
{
	name = newName;
	userName = newUserName;
	password = newPassword;
	id = newID;
}

void User::setName(string newName)
{
	name = newName;
}
    
void User::setUserName(string newUserName)
{
	userName = newUserName;
}

void User::setPassword(string newPassword)
{
	password = newPassword;
}

void User::setID(int newID)
{
	id = newID;
}
