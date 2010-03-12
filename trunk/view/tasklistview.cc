/*
 * tasklistview.cc
 *
 *  Created on: Mar 11, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "view/tasklistview.h"

/**
 * Constructor
 */
TaskListView::TaskListView(QWidget *parent) : QDialog(parent) {

    FormLayoutPtr layout(this);

    //Add layout
    task_list = layout << "Select a Task" |= new ModelListWidget<CommitteeModel>;


    //Button Creation and Additions
    add_button = new QPushButton("Add Task");
    edit_button = new QPushButton("Edit task");
    delete_button = new QPushButton("Delete Task");

    layout << add_button | edit_button | delete_button;

    //misc
    setModal(true);
    setWindowTitle("Add Task");

    //Connect slots/signals
    connect(add_button, SIGNAL(clicked()), this, SLOT(addTasks()));
    connect(edit_button, SIGNAL(clicked()), this, SLOT(editTasks()));
    connect(delete_button, SIGNAL(clicked()), this, SLOT(deleteTasks()));
}

TaskListView::~TaskListView(void) {}

void TaskListView::addTasks() {
    AddTaskView *addTaskDialog = new AddTaskView;
    addTaskDialog->show();
    if(addTaskDialog->exec() == QDialog::Accepted) {
    }
    delete addTaskDialog;
}

void TaskListView::editTasks() {

}

void TaskListView::deleteTasks() {
}

