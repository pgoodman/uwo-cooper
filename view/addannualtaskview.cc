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
    // Set up the form layout
    FormLayoutPtr layout(this);

    // Get the committee we're working with
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

    // Connect the buttons to respective functions
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
    // Check to see that the task at least has a name
    if(!name->isModified()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a task name"
        );
        return;
    }

    // Add the annual task spec to the committee
    committee->addTaskSpec(
        name->text(),
        description->toPlainText(),
        deadline->dateTime()
    );
    done(QDialog::Accepted);
}
