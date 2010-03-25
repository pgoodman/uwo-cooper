/*
 * addannualtaskview.cc
 *
 *  Created on: Mar 24, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "addannualtaskview.h"

/**
 * Constructor, build the add task form.
 */

AddAnnualTaskView::AddAnnualTaskView(CommitteeModel *comm, QWidget *parent) : QDialog(parent) {
    FormLayoutPtr layout(this);

    committee = comm;

    // Form Layout
    name = layout << "Task Name: " |= new QLineEdit;
    description = layout << "Description: " |= new QTextEdit;
    deadline = layout << "Deadline: " |= new QDateEdit;

    // Button Creation and Addition
    save_button = new QPushButton("Add");
    QPushButton *cancel(new QPushButton("Cancel"));
    layout << save_button | cancel;

    //Set up extra specifications
    deadline->setCalendarPopup(true);
    setModal(true);
    setWindowTitle("Add Annual Task Spec");

    connect(save_button, SIGNAL(clicked()), this, SLOT(save()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}


/**
 * Destructor.
 */
AddAnnualTaskView::~AddAnnualTaskView(void) {}

/**
 * Attempt to add a task.
 */
void AddAnnualTaskView::save(void) {
    if(!name->isModified()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a task name"
        );
        return;
    }

    committee->addTaskSpec(
        name->text(),
        description->toPlainText(),
        deadline->dateTime()
    );
    done(QDialog::Accepted);
}
