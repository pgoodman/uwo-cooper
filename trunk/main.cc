
#include <iostream>

#include <QtGui>
#include <QApplication>
#include <QMessageBox>

#include "view/initwizard.h"
#include "view/login.h"
#include "view/cooper.h"

#include "cooperdb.h"
#include "criticalerror.h"

#define D(x) x

using namespace std;

int main(int argc, char *argv[])
{

    QApplication cooperApp(argc, argv);

    try {
        //create DB object
        CooperDB::connect("cooper");

        //if coordinator was not setup
        if(!CooperDB::hasCoordinator()) {
            D( cout << "no coordinator" << endl; )
            InitWizard wizard;
            wizard.show();
            cooperApp.exec();
        } else {
            D( cout << "has coordinator" << endl; )
            Login login;
            login.show();
            cooperApp.exec();
        }

        //if UserController::activeUser is not null
        /*if(true){
            Cooper cooperUI;
            cooperUI.show();
            return cooperApp.exec();
        } else {
            return 0;
        }*/
    } catch(CriticalError &e) {
        D( cout << "Error: " << e.header() << endl << e.what() << endl; )
        QMessageBox::critical(0, e.header(), e.what(), QMessageBox::Cancel);
    } catch(...) {

    }
return 0;
}
