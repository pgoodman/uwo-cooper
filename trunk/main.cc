
#include <iostream>
#include <utility>

#include <QtGui>
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QWidget>

#include "view/login.h"
#include "view/window.h"

#include "conf.h"
#include "cooperdb.h"
#include "criticalerror.h"
#include "datatype/coordinator.h"
#include "datatype/unit.h"
#include "datatype/member.h"
#include "datatype/user.h"
#include "controller/setupcontroller.h"
#include "view/login.h"

using namespace std;

int main(int argc, char *argv[]) {

    static QApplication app(argc, argv);
    QMainWindow *window(Window::create());

    try {
        CooperDB::connect("cooper");

        if(!Coordinator::exists() || !Unit::exists()) {
            SetupController::install();
        } else {
            UserController::login();
        }
        window->show();
        return app.exec();


    } catch(CriticalError &e) {
        D( cout << "Error: " << e.header() << endl << e.what() << endl; )
        QMessageBox::critical(
            0,
            QString(e.header()),
            QString(e.what()),
            QMessageBox::Cancel
        );
        return 0;
    } catch(...) {
        cout << "Unkown Error Occured." << endl;
        return 0;
    }
}
