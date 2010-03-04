
#include "user.h"

map<int, User *> User::elms;

User::User()
{
	/*full_name = newName;
	userName = newUserName;
	password = newPassword;
	id = newID;*/
}

bool User::remove(void) {
    elms.erase(id);
    return CooperDB::remove("user", id);
}

/*
void User::setName(QString newName)
{
	name = newName;
}
    
void User::setUserName(QString newUserName)
{
	userName = newUserName;
}

void User::setPassword(QString newPassword)
{
	password = newPassword;
}

void User::setID(int newID)
{
	id = newID;
}
*/

bool User::hasPassword(QString &pass) {
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
