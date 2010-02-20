#include "cooper.h"
#include "ui_cooper.h"

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


