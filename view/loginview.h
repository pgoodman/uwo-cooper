#ifndef LOGIN_H
#define LOGIN_H

#include <string>

#include <QtGui>
#include <QGridLayout>
#include <QDialog>
#include <QPixmap>

#include "lib/gui/formlayoutptr.h"
#include "controller/usercontroller.h"

class LoginView : public QDialog
{
    Q_OBJECT
public:
    LoginView();
private:
    QLabel *titleLabel;
    QLabel *logo;
    QLineEdit *nameLineEdit;
    QLineEdit *pwdLineEdit;
private slots:
    void tryLogin();
};

#endif // LOGIN_H
