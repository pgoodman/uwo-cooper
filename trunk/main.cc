
#include <QApplication>
#include <QMessageBox>

#include "cooper.h"
#include "cooperdb.h"

#include "view/initwizard.h"
#include "view/login.h"


int main(int argc, char *argv[])
{

    QApplication cooperApp(argc, argv);

    try {
        //create DB object
        CooperDB db("cooper");

        //if coordinator was not setup
        if(!db->hasCoordinator()){
            InitWizard wizard;
            wizard.show();
            cooperApp.exec();
        } else {
            Login login;
            login.show();
            cooperApp.exec();
        }

        //if UserController::activeUser is not null
        if(true){
            Cooper cooperUI;
            cooperUI.show();
            return cooperApp.exec();
        } else {
            return 0;
        }
    } catch(...) {

    }



}
