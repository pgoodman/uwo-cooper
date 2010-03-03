
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

User *User::load(const unsigned int id) {
    if(0 != users[id]) {
        return users[id];
    }
    return 0;
}

User *User::load(string &user_name, string &pass) {
    (void) user_name;
    (void) pass;
    return 0;
}
