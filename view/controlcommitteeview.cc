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

    QFormLayout *layout = new QFormLayout(this);
    QVBoxLayout *column = new QVBoxLayout();

    setGeometry(QRect(20, 20, 441, 231));

    layout->setSpacing(6);
    layout->setContentsMargins(11, 11, 11, 11);
    layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    layout->setContentsMargins(0, 0, 0, 0);

    column->setSpacing(0);

    add_button = new QPushButton("Add Committee");
    edit_button = new QPushButton("Edit Committee");
    del_button = new QPushButton("Delete Committee");
    task_button = new QPushButton("Manage Tasks");

    connect(add_button, SIGNAL(clicked()), this, SLOT(addCommittee()));
    connect(edit_button, SIGNAL(clicked()), this, SLOT(editCommittee()));
    connect(del_button, SIGNAL(clicked()), this, SLOT(deleteCommittee()));
    connect(task_button, SIGNAL(clicked()), this, SLOT(viewTasks()));

    connect(
        committee_list,
        SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
        this,
        SLOT(activateButtons(QListWidgetItem *, QListWidgetItem *))
    );

    column->addWidget(add_button);
    column->addWidget(edit_button);
    column->addWidget(del_button);
    column->addWidget(task_button);

    layout->setLayout(0, QFormLayout::FieldRole, column);
    layout->setWidget(0, QFormLayout::LabelRole, committee_list);

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
void ControlCommitteeView::activateButtons(QListWidgetItem *old,
                                           QListWidgetItem *curr) {
    (void) old; (void) curr;

    CommitteeModel *committee(committee_list->getModel());
    if(0 == committee) {
        return;
    }

    edit_button->setDisabled(false);
    task_button->setDisabled(false);
    del_button->setDisabled(!committee->canRemove());
}
