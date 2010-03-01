#include "cooper.h"
#include "ui_cooper.h"
#include "controller/usercontroller.h"

Cooper::Cooper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cooper)
{
    ui->setupUi(this);

}

Cooper::~Cooper()
{
    delete ui;
}

void Cooper::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



void Cooper::on_actionLogoff_triggered()
{
    //user logoff
    //set avtive user to 0
    UserController::setActiveUser(0);
}

void Cooper::on_actionAdd_Member_triggered()
{
    //add member
}

void Cooper::on_actionEdit_Member_triggered()
{
    //edit member info
}

void Cooper::on_actionDelete_Member_triggered()
{
    //delete member
}

void Cooper::on_actionAdd_Committee_triggered()
{
    //add committee
}

void Cooper::on_actionDelete_Committee_triggered()
{
    //delete committee
}

void Cooper::on_actionAssign_Task_triggered()
{
    //assign task
}

void Cooper::on_actionEdit_Task_triggered()
{
    //edit task info
}

void Cooper::on_actionDelete_Task_triggered()
{
    //delete task
}

void Cooper::on_actionMove_Out_triggered()
{
    //trigger move out event
}

void Cooper::on_actionInternal_Move_triggered()
{
    //trigger internal move event
}

void Cooper::on_actionAnnual_Task_Spec_triggered()
{
    //trigger annual task specs
}

void Cooper::on_actionPhone_List_triggered()
{
    //print member phone list
}

void Cooper::on_actionCommittee_List_triggered()
{
    //print committee list
}

void Cooper::on_actionTask_List_triggered()
{
    //print task list
}

void Cooper::on_actionManual_triggered()
{
    //display manual
}

void Cooper::on_actionAbout_Cooper_triggered()
{
    //display name, version, credit info
}
