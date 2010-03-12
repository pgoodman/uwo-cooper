#ifndef LOGIN_H
#define LOGIN_H

#include <string>

#include <QtGui>
#include <QGridLayout>
#include <QDialog>

#include "lib/gui/formlayoutptr.h"
#include "controller/usercontroller.h"

class LoginView : public QDialog
{
    Q_OBJECT
public:
    LoginView();
private:
    QLabel *titleLabel;
    QLineEdit *nameLineEdit;
    QLineEdit *pwdLineEdit;
private slots:
    void tryLogin();
};

#endif // LOGIN_H
