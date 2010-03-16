#include "printcontroller.h"

PrintController::PrintController(int type){
    doctype = type;
    sort_method = SORT_BY_LASTNAME;
    print();
}
PrintController::~PrintController(){
}

void PrintController::print(){

    QDialog *pdialog = new QDialog();

    QGridLayout *layout = new QGridLayout();
    QRadioButton *sort_by_lastname = new QRadioButton("Sort by Last Name");
    QRadioButton *sort_by_unit = new QRadioButton("Sort by Unit");

    QButtonGroup *buttongrp = new QButtonGroup(pdialog);
    buttongrp->addButton(sort_by_lastname, 0);
    buttongrp->addButton(sort_by_unit, 1);
    sort_by_lastname->setChecked(true);

    QPushButton *ok = new QPushButton("OK");
    QPushButton *cancel = new QPushButton("Cancel");

    layout->addWidget(sort_by_lastname,0,0,1,2);
    layout->addWidget(sort_by_unit,1,0,1,2);
    layout->addWidget(ok, 2,0,1,1);
    layout->addWidget(cancel,2,1,1,1);

    connect(ok, SIGNAL(clicked()), pdialog, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), pdialog, SLOT(reject()));
    connect(buttongrp, SIGNAL(buttonClicked(int)), this, SLOT(sortingChanged(int)));

    pdialog->setWindowTitle("List Sorting Options");
    pdialog->setLayout(layout);
    pdialog->setModal(true);

    if(pdialog->exec() == QDialog::Accepted) {
        printer = new QPrinter(QPrinter::PrinterResolution);
        QPrintDialog *printDialog = new QPrintDialog(printer, 0);
        if(printDialog->exec() == QDialog::Accepted) {
              Document *doc = new Document(doctype);
              doc->print(printer);
        }
    }
}

void PrintController::sortingChanged(int sort){
    if(sort == 0) {
        sort_method = SORT_BY_LASTNAME;
    }else {
        sort_method = SORT_BY_UNIT;
    }
}
