
#include "usercontroller.h"

QWidget *UserController::curr_ui;

UserController::UserController()
{
}

UserController::~UserController() {

}

void UserController::home(void) {
    /*curr_ui = new Cooper;
    curr_ui->show();*/
    cout << "changing to ui cooper layout." << endl;
    Window::setWidget(new Ui_Cooper);
}

bool UserController::authorize(QString name, QString pwd) {
    bool match(name == COORDINATOR_USER_NAME);
    cout << "name is coord? " << match << endl;
    User* active(
        (name == COORDINATOR_USER_NAME) ? Coordinator::load(pwd)
                                        : Member::load(name, pwd)
    );

    if(0 == active || active->isSoftDeleted()) {
        return false;
    }

    User::setActive(active);
    return 0 != active;
}

void UserController::login() {
    //Login *login(new Login);
    //login->show();
    Window::setWidget(new Login);
}

void UserController::logout() {
    User::setActive(0);
    /*QWidget *login(new Login);
    login->show();
    curr_ui->hide();
    delete curr_ui;
    curr_ui = login;*/
    Window::setWidget(new Login);
}

