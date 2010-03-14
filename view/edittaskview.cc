/*
 * edittaskview.cc
 *
 *  Created on: Mar 13, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "edittaskview.h"

EditTaskView::EditTaskView(TaskModel *chosenTask,
                           CommitteeModel *comm,
                           QWidget *parent)
 : AddTaskView(comm, parent) {
    task = chosenTask;
    setWindowTitle("Edit Task");
    dataInit();
}

void EditTaskView::dataInit(void) {
    name->setText(task->getName());
    description->setText(task->getDescription());
    deadline->setDateTime(task->getDeadline());

    pending_status->setChecked(!task->isCompleted());
    completed_status->setChecked(task->isCompleted());

    pending_status->setDisabled(false);
    completed_status->setDisabled(false);
    name->setDisabled(true);
    description->setDisabled(true);
    deadline->setDisabled(true);
    save_button->setText("Update");
}

void EditTaskView::save(void) {
   task->setCompleted(completed_status->isChecked());
   task->save();
   emit accept();
}
