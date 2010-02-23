#include "usercontroller.h"

User *UserController::activeUser;

UserController::UserController()
{
}

UserController::~UserController() {
    delete activeUser;
}

int UserController::addUserAccount(string *name, string *pwd) {
    return 0;
}

int UserController::changeUserInfo(string *attribute, string *value) {
    return 0;
}
int UserController::userLogin(string *name, string *pwd){
    if (AuthorizationController::isValid(name, pwd))
        activeUser=AuthorizationController::getUser(name);
    return 0;
}
void UserController::userLogoff(){

}
