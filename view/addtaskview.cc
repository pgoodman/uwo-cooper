/*
 * addtaskview.cc
 *
 *  Created on: Mar 11, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "addtaskview.h"

/**
 * Constructor, build the add task form.
 */

AddTaskView::AddTaskView(QWidget *parent) : QDialog(parent) {
    FormLayoutPtr layout(this);

    // Status Button Group
    QButtonGroup *status_group(new QButtonGroup);
    QRadioButton *completed_status(new QRadioButton("Completed"));
    pending_status = new QRadioButton("Pending");
    status_group->addButton(pending_status);
    status_group->addButton(completed_status);

    // Form Layout
    name = layout << "Task Name: " |= new QLineEdit;
    description = layout << "Description: " |= new QTextEdit;
    layout << "Status?: " | pending_status;
    layout << "" | completed_status;
    deadline = layout << "Deadline: " |= new QDateEdit;

    // Button Creation and Addition
    QPushButton *add(new QPushButton("Add"));
    QPushButton *cancel(new QPushButton("Cancel"));
    layout << add | cancel;

    //Set up radio buttons
    pending_status->setChecked(true);
    deadline->setCalendarPopup(true);
    setModal(true);
    setWindowTitle("Add Task");

    connect(add, SIGNAL(clicked()), this, SLOT(addMember()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelAdd()));
}


/**
 * Destructor.
 */
AddTaskView::~AddTaskView(void) {}

/**
 * Attempt to add a task.
 */
void AddTaskView::addTask(void) {
    if(!name->isModified()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a surname (family name)."
        );
        return;
  }
    done(QDialog::Accepted);
}

/**
 * Close the add task window.
 */
void AddTaskView::cancelTask(void) {
    done(QDialog::Rejected);
}

