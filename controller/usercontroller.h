#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

using namespace std;
#include <string>
#include "datatype/user.h"
#include "controller/authorizationcontroller.h"

class UserController
{
public:
    UserController();
    ~UserController();
    static int addUserAccount(string *name, string *pwd);
    static int changeUserInfo(string *attribute, string *value);
    static int userLogin(string *name, string *pwd);
    static void userLogoff();
private:
    static User *activeUser;
};

#endif // USERCONTROLLER_H
