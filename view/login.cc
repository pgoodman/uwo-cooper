#include "login.h"

Login::Login() : QWidget(0) {
    titleLabel=new QLabel("Please enter login name and password.");
    nameLabel=new QLabel("Login Name: ");
    pwdLabel=new QLabel("Password: ");
    nameLineEdit=new QLineEdit;
    pwdLineEdit=new QLineEdit;
    pwdLineEdit->setEchoMode(QLineEdit::Password);
    okPushButton=new QPushButton("Login");
    cancelPushButton=new QPushButton("Cancel");

    QGridLayout *layout(new QGridLayout);
    layout->addWidget(titleLabel,0,0,1,2);
    layout->addWidget(nameLabel,1,0);
    layout->addWidget(nameLineEdit,1,1);
    layout->addWidget(pwdLabel,2,0);
    layout->addWidget(pwdLineEdit,2,1);
    layout->addWidget(okPushButton,3,0);
    layout->addWidget(cancelPushButton,3,1);

    setLayout(layout);

    QObject::connect(okPushButton, SIGNAL(clicked()),
                    this, SLOT(tryLogin()));
    QObject::connect(cancelPushButton, SIGNAL(clicked()),
                    this, SLOT(cancelLogin()));

    Window::setTitle("Log In to Cooper");
}

/**
 * Handle clicking the login button.
 */
void Login::tryLogin() {
    if(!UserController::authorize(nameLineEdit->text(), pwdLineEdit->text())) {
        cout << "Failed to log in. " << endl;
        titleLabel->setText(
            "Login name and password don't match. Please try again."
        );
    } else {
        UserController::home();
    }
}

/**
 * Handle pressing cancel.
 */
void Login::cancelLogin() {
    Window::close();
}
