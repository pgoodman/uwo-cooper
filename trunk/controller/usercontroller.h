#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <string>
#include <iostream>

#include <QApplication>
#include <QWidget>

#include "conf.h"

#include "view/homeview.h"
#include "view/loginview.h"

#include "model/usermodel.h"
#include "model/membermodel.h"
#include "model/coordinatormodel.h"

using namespace std;

class UserController {
public:
    ~UserController();
    static void home(void);
    static bool authorize(QString name, QString pwd);
    static void login(QWidget *window);
    static int login();
    static void logout();
private:
    static QMainWindow *home_view;
    UserController();
};

#endif // USERCONTROLLER_H
