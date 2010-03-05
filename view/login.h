#ifndef LOGIN_H
#define LOGIN_H

#include <string>

#include <QtGui>
#include <QGridLayout>

#include "window.h"
#include "controller/authorizationcontroller.h"
#include "controller/usercontroller.h"

class Login : public QWidget
{
    Q_OBJECT
public:
    Login();
private:
    QLabel *titleLabel;
    QLabel *nameLabel;
    QLabel *pwdLabel;
    QLineEdit *nameLineEdit;
    QLineEdit *pwdLineEdit;
    QPushButton *okPushButton;
    QPushButton *cancelPushButton;
private slots:
    void tryLogin();
    void close();
};

#endif // LOGIN_H
