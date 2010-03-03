
#include "user.h"

vector<User *> User::users;

User::User()
{
	/*full_name = newName;
	userName = newUserName;
	password = newPassword;
	id = newID;*/
}

/*
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
*/

void User::setFullName(string fullName)
{
    full_name = fullName;
}

bool User::hasPassword(string &pass) {
    return password == pass;
}
