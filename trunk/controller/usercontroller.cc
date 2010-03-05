
#include "usercontroller.h"

User *UserController::activeUser;

UserController::UserController()
{
}

UserController::~UserController() {
    delete activeUser;
}

void UserController::home(void) {
    Cooper cooperUI;
    cooperUI.show();
}

bool UserController::authorize(QString name, QString pwd) {
    bool match(name == COORDINATOR_USER_NAME);
    cout << "name is coord? " << match << endl;
    activeUser = (name == COORDINATOR_USER_NAME)
               ? Coordinator::load(pwd)
               : Member::load(name, pwd);
    return 0 != activeUser;
}

int UserController::login(QApplication &app) {
    Login login;
    login.show();
    return app.exec();
}

void UserController::logout() {
    activeUser = 0;
}

