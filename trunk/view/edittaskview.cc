/*
 * edittaskview.cc
 *
 *  Created on: Mar 13, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "edittaskview.h"

EditTaskView::EditTaskView(TaskModel *chosenTask, QWidget *parent)
 : QDialog(parent) {

    FormLayoutPtr layout(this);

    task = chosenTask;
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
    QPushButton *ok(new QPushButton("Ok"));
    QPushButton *cancel(new QPushButton("Cancel"));
    layout << ok | cancel;

    //Set up radio buttons
    pending_status->setChecked(true);
    pending_status->setEnabled(true);
    completed_status->setEnabled(true);
    name->setEnabled(false);
    description->setEnabled(false);
    deadline->setEnabled(false);
    deadline->setCalendarPopup(true);
    setModal(true);
    setWindowTitle("Add Task");

    connect(ok, SIGNAL(clicked()), this, SLOT(okTask()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelTask()));

    dataInit();
}

/**
 * Destructor.
 */
EditTaskView::~EditTaskView() {

}

void EditTaskView::dataInit(){
    name->setText(task->getName());
    description->setText(task->getDescription());
    deadline->setDateTime(task->getDeadline());
    bool status = task->getStatus();
    if (status == false)
        pending_status->setChecked(true);
    else
        pending_status->setChecked(false);
}

void EditTaskView::saveChange(){
   if (pending_status->isChecked() == true)
       task->setStatus(false);
   else
       task->setStatus(true);
   task->save();
}

void EditTaskView::okTask(void) {
    saveChange();
    done(QDialog::Accepted);
}

void EditTaskView::cancelTask(void) {
    done(QDialog::Rejected);
}
