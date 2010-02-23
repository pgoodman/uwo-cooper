#include "authorizationcontroller.h"

AuthorizationController::AuthorizationController()
{
}

AuthorizationController::~AuthorizationController(){

}

bool AuthorizationController::isValid(string *name, string *pwd){

    return true;
}
User *AuthorizationController::getUser(string *name) {

    return new User();
}
