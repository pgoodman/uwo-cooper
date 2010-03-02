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
int UserController::userLogin(string *name, string *pwd){
    if (AuthorizationController::isValid(name, pwd)) {
        activeUser=UserController::getUser(name);
    }
    return 0;
}
void UserController::userLogoff(){

}
void UserController::setActiveUser(User *theUser){
    activeUser=theUser;
}
User *UserController::getUser(string *name){
    (void) name;
    return new User();
}
