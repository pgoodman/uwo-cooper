/*
 * tasklistview.cc
 *
 *  Created on: Mar 11, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "view/tasklistview.h"

/**
 * Constructor: Initialize the popup for managing a committee's tasks.
 */
TaskListView::TaskListView(CommitteeModel *comm, QWidget *parent)
 : QDialog(parent) {

    // Set up the form layout
    FormLayoutPtr layout(this);

    // Get the committee that we're working with
    committee = comm;

    //Add layout
    task_list = layout << "Select a Task" |= new ModelListWidget<TaskModel>;

    //Button Creation and Additions to Layout
    add_button = new QPushButton("Add Task");
    edit_button = new QPushButton("Edit task");
    delete_button = new QPushButton("Delete Task");

    add_annual_button = new QPushButton("Add Annual Task Spec");
    delete_annual_button = new QPushButton("Delete Annual Task Spec");
    activate_annual_button = new QPushButton("Activate Annual Task Specs");
    QPushButton *close_button = new QPushButton("Close");

    layout << add_button | edit_button | delete_button;
    annualTask_list = layout << "Select an Annual Task" |= new ModelListWidget<TaskSpecModel>;
    layout << add_annual_button | delete_annual_button | activate_annual_button;
    layout << close_button;

    // Check for permissions that the user has on each possible choice on the task list form
    if(!active_user->hasPermission(ADD_SELF_TASK)) {
        add_button->hide();
    }

    if(!active_user->hasPermission(EDIT_SELF_TASK)) {
        edit_button->hide();
    }

    if(!active_user->hasPermission(DELETE_SELF_TASK)) {
        delete_button->hide();
    }

    if (!active_user->hasPermission(ADD_SELF_TASK_SPEC)) {
        add_annual_button->hide();
    }

    if (!active_user->hasPermission(DELETE_SELF_TASK_SPEC)) {
        delete_annual_button->hide();
    }

    if (!active_user->hasPermission(ACTIVATE_SELF_TASK_SPEC)){
        activate_annual_button->hide();
    }

    //misc
    edit_button->setEnabled(false);
    delete_button->setEnabled(false);
    delete_annual_button->setEnabled(false);
    activate_annual_button->setEnabled(false);
    setModal(true);
    setWindowTitle("Manage Tasks");
    populateTaskList();
    populateAnnualTaskList();

    //Connect slots/signals
    connect(add_button, SIGNAL(clicked()), this, SLOT(addTasks()));
    connect(edit_button, SIGNAL(clicked()), this, SLOT(editTasks()));
    connect(delete_button, SIGNAL(clicked()), this, SLOT(deleteTasks()));
    connect(close_button, SIGNAL(clicked()), this, SLOT(accept()));
    connect(add_annual_button, SIGNAL(clicked()), this, SLOT(addAnnualTasks()));
    connect(delete_annual_button, SIGNAL(clicked()), this, SLOT(deleteAnnualTasks()));
    connect(activate_annual_button, SIGNAL(clicked()), this, SLOT(activateAnnualTasks()));
    connect(
        task_list, SIGNAL(itemSelectionChanged()),
        this, SLOT(activateButtons())
    );
    connect(
        annualTask_list, SIGNAL(itemSelectionChanged()),
        this, SLOT(activateSpecButtons())
    );

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
    edit_button->setEnabled(false);
    delete_button->setEnabled(false);
}

/**
  * Populate the annual task list
  */
void TaskListView::populateAnnualTaskList(void) {
    TaskSpecModel::iterator_range annualTasks(committee->findTaskSpecs());
    annualTask_list->fill(annualTasks);
    delete_annual_button->setEnabled(false);
    activate_annual_button->setEnabled(annualTasks.first != annualTasks.second);
}

/**
 * De/activate the various control buttons depending on the task selected.
 */

void TaskListView::activateButtons() {
    TaskModel *task(task_list->getSelectedModel());

    if(0 == task) {
        return;
    }

    // Depending on whether or not its completed, it can be edited or deleted
    bool is_completed(task->isCompleted());
    edit_button->setEnabled(!is_completed);
    delete_button->setEnabled(is_completed);
}

/**
  * De/activate the various control buttons depending on the annual task
  * selected.
  */
void TaskListView::activateSpecButtons() {
    TaskSpecModel *annualTask(annualTask_list->getSelectedModel());
    if(0 == annualTask) {
        return;
    }
    delete_annual_button->setEnabled(true);
}

/**
 * Pop up the add tasks view.
 */
void TaskListView::addTasks() {
    AddTaskView addTaskDialog(committee, this);
    if(QDialog::Accepted == addTaskDialog.exec()) {
        populateTaskList();
    }
}

/**
  * Pop up the add annual tasks view.
  */

void TaskListView::addAnnualTasks() {
    AddAnnualTaskView addAnnualTaskDialog(committee, this);
    if (QDialog::Accepted == addAnnualTaskDialog.exec()){
        populateAnnualTaskList();
    }

}

/**
 * Pop up the edit tasks view.
 */
void TaskListView::editTasks() {
    EditTaskView editTaskDialog(task_list->getSelectedModel(), committee, this);
    if (QDialog::Accepted == editTaskDialog.exec()) {
        populateTaskList();
    }
}

/**
 * Delete a task.
 */
void TaskListView::deleteTasks() {
    TaskModel *task(task_list->getSelectedModel());
    if(0 != task) {
        int ret(QMessageBox::question(this,
            "Please Confirm",
            "Are you sure that you want to delete the task?",
            QMessageBox::Yes,
            QMessageBox::No
        ));
        if(QMessageBox::Yes == ret) {
            task->remove();
            populateTaskList();
        }
    }
}

/**
  * Delete an annual task.
  */

void TaskListView::deleteAnnualTasks() {
    TaskSpecModel *annualTask(annualTask_list->getSelectedModel());
    if(0 != annualTask) {
        int ret(QMessageBox::question(this,
            "Please Confirm",
            "Are you sure that you want to delete the annual task?",
            QMessageBox::Yes,
            QMessageBox::No
        ));
        if(QMessageBox::Yes == ret) {
            annualTask->remove();
            populateAnnualTaskList();
        }
    }
}

/**
  * Pop up the activate annual task view
  */

void TaskListView::activateAnnualTasks() {
    ActivateAnnualTaskView activateTaskDialog(committee, this);
    if (QDialog::Accepted == activateTaskDialog.exec()) {
        populateTaskList();
    }
}
