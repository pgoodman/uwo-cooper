#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <string>
#include "datatype/user.h"
#include "datatype/member.h"
#include "datatype/coordinator.h"
#include "authorizationcontroller.h"
#include "conf.h"

using namespace std;

class UserController
{
public:
    UserController();
    ~UserController();
    static int addUserAccount(string *name, string *pwd);
    static int changeUserInfo(string *attribute, string *value);
    static int login(QString name, QString pwd);
    static void logout();
    static User *activeUser;
};

#endif // USERCONTROLLER_H
