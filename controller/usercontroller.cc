#include "usercontroller.h"

User *UserController::activeUser;

UserController::UserController()
{
}

UserController::~UserController() {
    delete activeUser;
}

int UserController::addUserAccount(string *name, string *pwd) {
    (void) name; (void) pwd;
    return 0;
}

int UserController::changeUserInfo(string *attribute, string *value) {
    (void) attribute;
    (void) value;
    return 0;
}
int UserController::login(string name, string pwd){
    activeUser = User::load(name, pwd);
    return 0 != activeUser;
}
void UserController::logout() {
    activeUser = 0;
}

