
#include "view/loginview.h"

LoginView::LoginView() : QDialog(0) {
    setModal(true);
    this->setFixedSize(300,150);
    QPalette palette;
    QPixmap bgimage = QPixmap(QString("../images/flowershort.jpg"));
    bgimage.scaledToWidth(300);
    bgimage.scaledToHeight(150);
    palette.setBrush(QPalette::Window,bgimage);
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    FormLayoutPtr layout(this);

    titleLabel = layout [2] <<= "Please enter login name and password.";
    QFont font;
    font.setPointSize(8);
    font.setBold(true);
    titleLabel->setFixedSize(225,25);
    titleLabel->setFont(font);
    titleLabel->setAutoFillBackground(true);

    //logo = new QLabel();
    //logo->setPixmap(QPixmap("../images/flowershort.jpg"));
    //layout |= logo;
    nameLineEdit = layout << "Login Name: " |= new QLineEdit;
    pwdLineEdit = layout << "Password: " |= new QLineEdit;
    QPushButton *okPushButton(layout <<= new QPushButton("Login"));
    QPushButton *cancelPushButton(layout |= new QPushButton("Cancel"));
    okPushButton->setDefault(true);
    connect(
        okPushButton, SIGNAL(clicked()),
        this, SLOT(tryLogin())
    );

    connect(
        cancelPushButton, SIGNAL(clicked()),
        this, SLOT(reject())
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
