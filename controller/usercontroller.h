#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <string>
#include <iostream>

#include <QApplication>

#include "authorizationcontroller.h"
#include "conf.h"

#include "view/cooper.h"
#include "view/login.h"

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
    static int login(QApplication &);
    static void logout();
    static User *activeUser;
private:
    UserController();
};

#endif // USERCONTROLLER_H
