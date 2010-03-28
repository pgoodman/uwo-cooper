/*
 * edittaskview.cc
 *
 *  Created on: Mar 13, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "edittaskview.h"

/**
  * Constructor
  */

EditTaskView::EditTaskView(TaskModel *chosenTask,
                           CommitteeModel *comm,
                           QWidget *parent)
 : AddTaskView(comm, parent) {
    task = chosenTask;
    setWindowTitle("Edit Task");
    dataInit();
}

/**
  * Initialize the data to be edited/shown on the form.
  */

void EditTaskView::dataInit(void) {
    // Insert the task's data into the respective text boxes.
    name->setText(task->getName());
    description->setText(task->getDescription());
    deadline->setDateTime(task->getDeadline());

    // Set the status of the task depending on whether it is already completed or not.
    pending_status->setChecked(!task->isCompleted());
    completed_status->setChecked(task->isCompleted());

    // Allow only the status to be edited while everything else can only be read.
    pending_status->setDisabled(false);
    completed_status->setDisabled(false);
    name->setDisabled(true);
    description->setDisabled(true);
    deadline->setDisabled(true);
    save_button->setText("Update");
}

/**
  * Save the edited data
  */

void EditTaskView::save(void) {
   task->setCompleted(completed_status->isChecked());
   task->save();
   emit accept();
}
