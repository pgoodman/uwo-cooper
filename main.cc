
#include <iostream>
#include <utility>

#include <QtGui>
#include <QApplication>
#include <QMessageBox>
#include <QString>

#include "view/login.h"
#include "view/cooper.h"

#include "conf.h"
#include "cooperdb.h"
#include "criticalerror.h"
#include "datatype/coordinator.h"
#include "datatype/member.h"
#include "datatype/user.h"
#include "controller/setupcontroller.h"
#include "view/initwizard.h"
#include "view/login.h"

using namespace std;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    try {
        //create DB object
        CooperDB::connect("cooper");

        //if coordinator was not setup
        if(!Coordinator::exists()) {
            //D( cout << "no coordinator" << endl; )
            InitWizard wizard;
            wizard.show();
            SetupController::addCoordinator();
            return app.exec();

           /*Cooper cooperUI;
           cooperUI.show();
           return app.exec();*/

        } else {
            //D( cout << "has coordinator" << endl; )
            Login login;
            login.show();
            return app.exec();
        }

        //if UserController::activeUser is not null
        if(!UserController::activeUser){

            return app.exec();
        } else {
            return 0;
        }

    } catch(CriticalError &e) {
        D( cout << "Error: " << e.header() << endl << e.what() << endl; )
        QMessageBox::critical(
            0,
            QString(e.header()),
            QString(e.what()),
            QMessageBox::Cancel
        );
    } catch(...) {
        return 1;
    }
    return app.exec();
}
