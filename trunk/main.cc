#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "cooper.h"
#include "initwizard.h"
#include "cooperdb.h"
#include "login.h"


int main(int argc, char *argv[])
{

    QApplication cooperApp(argc, argv);

    //create DB object
    CooperDB *db=new CooperDB();

    //if coordinator was not setup
    if(!db->hasCoordinator()){
        InitWizard wizard;
        wizard.show();
        cooperApp.exec();
    }
    else {
        Login login;
        login.show();
        cooperApp.exec();
    }

    //if UserController::activeUser is not null
    if(true){
        Cooper cooperUI;
        cooperUI.show();
        return cooperApp.exec();
    }
    else
        return 0;



}
