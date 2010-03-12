/*
 * tasklistview.cc
 *
 *  Created on: Mar 11, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "view/tasklistview.h"

/**
 * Initialize the popup for managing a committee's tasks.
 */
TaskListView::TaskListView(CommitteeModel *comm, QWidget *parent)
 : QDialog(parent) {

    committee = comm;
    FormLayoutPtr layout(this);

    //Add layout
    task_list = layout << "Select a Task" |= new ModelListWidget<TaskModel>;

    //Button Creation and Additions
    add_button = new QPushButton("Add Task");
    edit_button = new QPushButton("Edit task");
    delete_button = new QPushButton("Delete Task");
    QPushButton *close_button = new QPushButton("Close");

    layout << add_button | edit_button | delete_button | close_button;

    //misc
    setModal(true);
    setWindowTitle("Add Task");
    populateTaskList();

    //Connect slots/signals
    connect(add_button, SIGNAL(clicked()), this, SLOT(addTasks()));
    connect(edit_button, SIGNAL(clicked()), this, SLOT(editTasks()));
    connect(delete_button, SIGNAL(clicked()), this, SLOT(deleteTasks()));
    connect(close_button, SIGNAL(clicked()), this, SLOT(accept()));
}

/**
 * Destructor.
 */
TaskListView::~TaskListView(void) {

}

/**
 * Populate the task list.
 */
void TaskListView::populateTaskList(void) {
    TaskModel::iterator_range tasks(committee->findTasks());
    task_list->fill(tasks);
}

/**
 * Pop up the add tasks view.
 */
void TaskListView::addTasks() {
    AddTaskView addTaskDialog(this);
    if(QDialog::Accepted == addTaskDialog.exec()) {

    }
}

/**
 * Pop up the edit tasks view.
 */
void TaskListView::editTasks() {

}

/**
 * Delete a task.
 */
void TaskListView::deleteTasks() {

}

