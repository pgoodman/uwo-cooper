#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <string>
#include "datatype/user.h"
#include "authorizationcontroller.h"

using namespace std;

class UserController
{
public:
    UserController();
    ~UserController();
    static int addUserAccount(string *name, string *pwd);
    static int changeUserInfo(string *attribute, string *value);
    static int login(string name, string pwd);
    static void logout();
private:
    static User *activeUser;
};

#endif // USERCONTROLLER_H
