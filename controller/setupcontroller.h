#ifndef SETUPCONTROLLER_H
#define SETUPCONTROLLER_H

#include <QString>
#include "../datatype/user.h"

using namespace std;

//class string;

class SetupController
{
public:
    SetupController();
    ~SetupController();

    static int addCoordinator();
    static int loadData(QString file_name);
};

#endif // SETUPCONTROLLER_H
