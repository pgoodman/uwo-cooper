#ifndef SETUPCONTROLLER_H
#define SETUPCONTROLLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <locale>

#include <QString>
#include <QApplication>
#include <QMessageBox>

#include "datatype/user.h"
#include "view/initwizard.h"

using namespace std;

class SetupController
{
public:
    ~SetupController();

    static int install(QApplication &app);
    static bool loadData(QString file_name);
private:
    SetupController();
};

#endif // SETUPCONTROLLER_H
