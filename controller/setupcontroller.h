#ifndef SETUPCONTROLLER_H
#define SETUPCONTROLLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <locale>

#include <QString>
#include <QApplication>
#include <QMessageBox>

#include "criticalerror.h"

#include "view/setup.h"
#include "view/window.h"

#include "datatype/user.h"
#include "datatype/unit.h"

using namespace std;

class SetupController
{
public:
    ~SetupController();

    static void install();
    static bool loadData(QString file_name);
private:
    SetupController();
};

#endif // SETUPCONTROLLER_H
