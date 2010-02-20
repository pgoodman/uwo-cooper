#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "cooper.h"
#include "initwizard.h"


int main(int argc, char *argv[])
{

    QApplication cooperApp(argc, argv);


    //if coordinator was not setup
    if(true){
        InitWizard wizard;
        wizard.show();
        cooperApp.exec();
    }
    //if coordinator was setup and data loaded
    if(true){
        Cooper cooperUI;
        cooperUI.show();
        return cooperApp.exec();
    }




}
