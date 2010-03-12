#ifndef SETUPCONTROLLER_H
#define SETUPCONTROLLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <sstream>

#include <QString>
#include <QApplication>
#include <QMessageBox>

#include "view/setupview.h"

#include "model/usermodel.h"
#include "model/unitmodel.h"

using namespace std;

class SetupController
{
public:
    ~SetupController();

    static int install();
    static bool loadData(QString file_name);
private:
    SetupController();

    static bool error(const char *error);
    static bool parseFile(ifstream &file);
};

#endif // SETUPCONTROLLER_H
