
#include "user.h"

map<int, User *> User::elms;

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

string User::getFullName(void) {
    return full_name;
}

void User::setFullName(string fullName)
{
    full_name = fullName;
}

bool User::hasPassword(string &pass) {
    return password == pass;
}

void User::remember(const int id, User *val) {
    if(!remembered(id)) {
        elms[id] = val;
    }
}

User *User::recall(const int id) {
    if(!remembered(id)) {
        throw 0;
    }
    return elms[id];
}

bool User::remembered(const int id) {
    return elms.end() != elms.find(id);
}
