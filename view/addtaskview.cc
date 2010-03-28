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

AddTaskView::AddTaskView(CommitteeModel *comm, QWidget *parent) : QDialog(parent) {
    // Set up the form layout
    FormLayoutPtr layout(this);

    // Get the committee that we're working with
    committee = comm;

    // Status Button Group
    QButtonGroup *status_group(new QButtonGroup);
    completed_status = new QRadioButton("Completed");
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
    save_button = new QPushButton("Add");
    QPushButton *cancel(new QPushButton("Cancel"));
    layout << save_button | cancel;

    //Set up radio buttons
    pending_status->setChecked(true);
    pending_status->setEnabled(false);
    completed_status->setEnabled(false);
    deadline->setCalendarPopup(true);
    setModal(true);
    setWindowTitle("Add Task");

    // Connect the buttons to their respective functions
    connect(save_button, SIGNAL(clicked()), this, SLOT(save()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}


/**
 * Destructor.
 */
AddTaskView::~AddTaskView(void) {}

/**
 * Attempt to add a task.
 */
void AddTaskView::save(void) {

    // Check to see that the added task at least has a name
    if(!name->isModified()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a task name"
        );
        return;
    }

    // Add the task to the given committee
    committee->addTask(
        name->text(),
        description->toPlainText(),
        deadline->dateTime()
    );
    done(QDialog::Accepted);
}
