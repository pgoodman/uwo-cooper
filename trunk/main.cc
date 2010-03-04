
#include <iostream>

#include <QtGui>
#include <QApplication>
#include <QMessageBox>
#include <QString>

//#include "view/login.h"
#include "view/cooper.h"

#include "conf.h"
#include "cooperdb.h"
#include "criticalerror.h"
#include "datatype/coordinator.h"
#include "controller/setupcontroller.h"

using namespace std;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QWidget *window = new QWidget;

    try {
        //create DB object
        CooperDB::connect("cooper");

        //if coordinator was not setup
        if(!Coordinator::exists()) {
            D( cout << "no coordinator" << endl; )
            //InitWizard wizard(window);
            //wizard.show();
            SetupController::addCoordinator();

        } else {
            D( cout << "has coordinator" << endl; )
            //Login login;
            //login.show();
        }

        //if UserController::activeUser is not null
        /*if(true){
            Cooper cooperUI;
            cooperUI.show();
            return cooperApp.exec();
        } else {
            return 0;
        }*/

        window->show();

    } catch(CriticalError &e) {
        D( cout << "Error: " << e.header() << endl << e.what() << endl; )
        QMessageBox::critical(
            0,
            QString(e.header()),
            QString(e.what()),
            QMessageBox::Cancel
        );
    } catch(...) {

    }
    return app.exec();
}
