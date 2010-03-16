/*
 * committeecontrolview.cc
 *
 *  Created on: Mar 11, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "view/controlcommitteeview.h"

/**
 * Initialize the committee controls.
 */
ControlCommitteeView::ControlCommitteeView(QWidget *parent) : QWidget(parent) {
    committee_list = new ModelListWidget<CommitteeModel>(this);

    QGridLayout *layout = new QGridLayout(this);
    QVBoxLayout *column = new QVBoxLayout;

    setGeometry(QRect(20, 20, 441, 231));

    layout->setSpacing(6);
    layout->setContentsMargins(11, 11, 11, 11);
    column->setSpacing(0);

    add_button = new QPushButton("Add Committee");
    edit_button = new QPushButton("Edit Committee");
    del_button = new QPushButton("Delete Committee");
    task_button = new QPushButton("Manage Tasks");
    print_committee_button = new QPushButton("Print Committee List");
    print_task_button = new QPushButton("Pring Pending Tasks");

    if(!active_user->hasPermission(ADD_TASK | EDIT_TASK | DELETE_TASK)) {
        task_button->hide();
    }

    if(!active_user->hasPermission(ADD_COMMITTEE)) {
        add_button->hide();
    }
    if(!active_user->hasPermission(EDIT_COMMITTEE)) {
        edit_button->hide();
    }
    if(!active_user->hasPermission(DELETE_COMMITTEE)) {
        del_button->hide();
    }
    if(!active_user->hasPermission(PRINT_COMMITTEE_LIST)){
        print_committee_button->hide();
    }
    if(!active_user->hasPermission(PRINT_TASK_LIST)){
        print_task_button->hide();
    }
    connect(add_button, SIGNAL(clicked()), this, SLOT(addCommittee()));
    connect(edit_button, SIGNAL(clicked()), this, SLOT(editCommittee()));
    connect(del_button, SIGNAL(clicked()), this, SLOT(deleteCommittee()));
    connect(task_button, SIGNAL(clicked()), this, SLOT(viewTasks()));
    connect(print_task_button,SIGNAL(clicked()), this, SLOT(printTask()));
    connect(print_committee_button, SIGNAL(clicked()), this, SLOT(printCommittee()));

    connect(
        committee_list, SIGNAL(itemSelectionChanged()),
        this, SLOT(activateButtons())
    );

    column->addWidget(add_button);
    column->addWidget(edit_button);
    column->addWidget(del_button);
    column->addWidget(task_button);
    column->addWidget(print_committee_button);
    column->addWidget(print_task_button);

    layout->addWidget(
        new QLabel("Select a committee from the list to toggle the controls."),
        1, 1, 1, 2
    );
    layout->addWidget(committee_list, 2, 1, 1, 1);
    layout->addLayout(column, 2, 2, 1, 1);

    populateCommittees();
}

/**
 * Update the committee list.
 */
void ControlCommitteeView::populateCommittees() {
    committee_list->fill(&CommitteeModel::findAll);
    edit_button->setDisabled(true);
    del_button->setDisabled(true);
    task_button->setDisabled(true);
    print_task_button->setDisabled(true);
}


/**
 * Pop up the add committee form.
 */
void ControlCommitteeView::addCommittee(){
    AddCommitteeView addCommitteeDialog;
    if(addCommitteeDialog.exec() == QDialog::Accepted) {
        populateCommittees();
    }
}

/**
 * Pop up a window to manage the tasks of a committee.
 */
void ControlCommitteeView::viewTasks() {
    CommitteeModel *committee(committee_list->getModel());
    if(0 != committee) {
        TaskListView viewTaskDialog(committee, this);
        viewTaskDialog.exec();
    }
}

/**
 * De/activate the various control buttons depending on the committee selected.
 */
void ControlCommitteeView::activateButtons() {
    CommitteeModel *committee(committee_list->getModel());
    if(0 == committee) {
        return;
    }

    edit_button->setDisabled(false);
    task_button->setDisabled(false);
    print_task_button->setDisabled(false);
    del_button->setDisabled(!committee->canRemove());
}

void ControlCommitteeView::deleteCommittee()
{
    CommitteeModel *committee(committee_list->getModel());

    if(committee != 0 && committee->canRemove())
    {
        int ret(QMessageBox::question(this,
            "Please Confirm",
            "Are you sure that you want to delete the committee?",
            QMessageBox::Yes,
            QMessageBox::No
        ));
        if(QMessageBox::Yes == ret) {
           committee->remove();
           populateCommittees();
        }
    } else {
        QMessageBox::information(this,
             "Can not delete",
             "The committee you have chosen doesn't exist, or "
             "cannot be deleted"
        );
        return;
    }
}

void ControlCommitteeView::printCommittee(){
    new PrintController(COMMITTEE_LIST);
}

void ControlCommitteeView::printTask(){
    new PrintController(TASK_LIST);
}
