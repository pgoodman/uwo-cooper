#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <string>
#include <iostream>

#include <QApplication>
#include <QWidget>

#include "authorizationcontroller.h"
#include "conf.h"

#include "view/ui_cooper.h"
#include "view/login.h"
#include "view/window.h"

#include "datatype/user.h"
#include "datatype/member.h"
#include "datatype/coordinator.h"

using namespace std;

class UserController
{
public:
    ~UserController();
    static void home(void);
    static bool authorize(QString name, QString pwd);
    static void login(QWidget *window);
    static void login();
    static void logout();
private:
    static QWidget *curr_ui;
    UserController();
};

#endif // USERCONTROLLER_H
