#include "login.h"

Login::Login():QWidget(){
    titleLabel=new QLabel("Please enter login name and password.");
    nameLabel=new QLabel("Login Name: ");
    pwdLabel=new QLabel("Password: ");
    nameLineEdit=new QLineEdit;
    pwdLineEdit=new QLineEdit;
    okPushButton=new QPushButton("Login");
    cancelPushButton=new QPushButton("Cancel");

    QGridLayout *layout=new QGridLayout;
    layout->addWidget(titleLabel,0,0,1,2);
    layout->addWidget(nameLabel,1,0);
    layout->addWidget(nameLineEdit,1,1);
    layout->addWidget(pwdLabel,2,0);
    layout->addWidget(pwdLineEdit,2,1);
    layout->addWidget(okPushButton,3,0);
    layout->addWidget(cancelPushButton,3,1);
    this->setLayout(layout);
    QObject::connect(okPushButton, SIGNAL(clicked()),
                    this, SLOT(on_loginPushButton_clicked()));
    QObject::connect(cancelPushButton, SIGNAL(clicked()),
                    this, SLOT(close()));
}

void Login::on_loginPushButton_clicked(){
    //handle login operation.
    //set proper active user in usercontroller class

    this->close();
}
