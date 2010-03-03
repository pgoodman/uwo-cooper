#ifndef SETUPCONTROLLER_H
#define SETUPCONTROLLER_H

#include <string>
#include "../datatype/user.h"

using namespace std;

//class string;

class SetupController
{
public:
    SetupController();
    ~SetupController();

    static int addCoordinator(string *name,string *pwd);
    static int loadData(string *filename);


};

#endif // SETUPCONTROLLER_H
