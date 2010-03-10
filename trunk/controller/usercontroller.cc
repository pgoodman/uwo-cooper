
#include "controller/usercontroller.h"

UserController::UserController() { }
UserController::~UserController() { }

void UserController::home(void) {
    HomeView *view(new HomeView);
    view->show();
}

bool UserController::authorize(QString name, QString pwd) {
    UserModel *active(0);
    if(name == COORDINATOR_USER_NAME) {
        active = CoordinatorModel::findByPassword(pwd);
    } else {
        MemberModel *member(MemberModel::findByLoginInfo(name, pwd));
        if(0 != member && !member->isMarkedDeleted()) {
            active = member;
        }
    }

    UserModel::setActive(active);

    return 0 != active;
}

int UserController::login() {
    LoginView login;
    return login.exec();
}

void UserController::logout() {
    UserModel::setActive(0);
}

