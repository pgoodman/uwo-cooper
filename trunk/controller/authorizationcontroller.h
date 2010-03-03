#ifndef AUTHORIZATIONCONTROLLER_H
#define AUTHORIZATIONCONTROLLER_H

#include <string>
#include "../datatype/user.h"

using namespace std;

class AuthorizationController
{
public:
    AuthorizationController();
    ~AuthorizationController();
    static bool isValid(string *name, string *pwd);
};

#endif // AUTHORIZATIONCONTROLLER_H
