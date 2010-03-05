
#include "usercontroller.h"

UserController::UserController()
{
}

UserController::~UserController() {

}

void UserController::home(void) {
    Cooper *ui(new Cooper);
    ui->show();
}

bool UserController::authorize(QString name, QString pwd) {
    bool match(name == COORDINATOR_USER_NAME);
    cout << "name is coord? " << match << endl;
    User* active(
        (name == COORDINATOR_USER_NAME) ? Coordinator::load(pwd)
                                        : Member::load(name, pwd)
    );
    if(active->isSoftDeleted()) {
        return false;
    }
    User::setActive(active);
    return 0 != active;
}

int UserController::login(QApplication &app) {
    Login login;
    login.show();
    return app.exec();
}

void UserController::logout() {
    User::setActive(0);
}

