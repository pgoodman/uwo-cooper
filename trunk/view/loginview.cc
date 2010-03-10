
#include "view/loginview.h"

LoginView::LoginView() : QDialog(0) {
    setModal(true);

    FormLayoutPtr layout(this);
    titleLabel = layout [2] <<= "Please enter login name and password." ;
    nameLineEdit = layout << "Login Name: " |= new QLineEdit;
    pwdLineEdit = layout << "Password: " |= new QLineEdit;
    QPushButton *okPushButton(layout <<= new QPushButton("Login"));
    QPushButton *cancelPushButton(layout |= new QPushButton("Cancel"));

    QObject::connect(
        okPushButton, SIGNAL(clicked()),
        this, SLOT(tryLogin())
    );

    QObject::connect(
        cancelPushButton, SIGNAL(clicked()),
        this, SLOT(cancelLogin())
    );

    setWindowTitle("Log In to Cooper");
    pwdLineEdit->setEchoMode(QLineEdit::Password);
}

/**
 * Handle clicking the login button.
 */
void LoginView::tryLogin() {
    QString uname(nameLineEdit->text());
    QString pass(pwdLineEdit->text());
    if(!UserController::authorize(uname, pass)) {
        cout << "Failed to log in. " << endl;
        titleLabel->setText(
            "Login name and password don't match anyone in the system. "
            "Please try again."
        );
    } else {
        done(QDialog::Accepted);
    }
}

/**
 * Handle pressing cancel.
 */
void LoginView::cancelLogin() {
    done(QDialog::Rejected);
}
