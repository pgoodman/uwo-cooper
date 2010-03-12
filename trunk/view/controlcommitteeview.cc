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

    QPushButton *add_button = new QPushButton("Add Committee");
    QPushButton *edit_button = new QPushButton("Edit Committee");
    QPushButton *del_button = new QPushButton("Delete Committee");
    QPushButton *task_button = new QPushButton("Tasks");

    connect(add_button, SIGNAL(clicked()), this, SLOT(addCommittee()));
    connect(edit_button, SIGNAL(clicked()), this, SLOT(editCommittee()));
    connect(del_button, SIGNAL(clicked()), this, SLOT(deleteCommittee()));
    connect(task_button, SIGNAL(clicked()), this, SLOT(viewTasks()));

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

void ControlCommitteeView::viewTasks() {
     TaskListView viewTaskDialog;
     if (viewTaskDialog.exec() == QDialog::Accepted) {
         //populate tasks
     }
}
