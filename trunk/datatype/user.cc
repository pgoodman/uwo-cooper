
#include "user.h"

map<int, User *> User::elms;
User *User::active = 0;

User::User(const int userId, const bool isCoordinator, QString pwd)
 : id(userId), is_coordinator(isCoordinator), password(pwd)
{
}

void User::setActive(User *u) {
    active = u;
}

bool User::canDo(const Permission p) {
    return (0 == active) ? false : active->hasPermission(p);
}

void User::softDelete(bool x) {
    (void) x;
    return;
}

void User::hardDelete(void) {
    return;
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
int User::getID(){
    return id;
}

bool User::hasPassword(QString &pass) {
    cout << "actual: " << password.toStdString() << " got: " << pass.toStdString() << endl;
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
