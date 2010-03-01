#ifndef AUTHORIZATIONCONTROLLER_H
#define AUTHORIZATIONCONTROLLER_H

using namespace std;
#include <string>
#include "datatype/user.h"

class AuthorizationController
{
public:
    AuthorizationController();
    ~AuthorizationController();
    static bool isValid(string *name, string *pwd);
};

#endif // AUTHORIZATIONCONTROLLER_H
