#ifndef SETUPCONTROLLER_H
#define SETUPCONTROLLER_H

#include <QString>
#include <QApplication>

#include "../datatype/user.h"

using namespace std;

//class string;

class SetupController
{
public:
    SetupController();
    ~SetupController();

    static int install(QApplication &app);
    static bool loadData(QString file_name);
};

#endif // SETUPCONTROLLER_H
