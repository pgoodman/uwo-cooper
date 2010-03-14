/*
 * membercontrolview.cc
 *
 *  Created on: Mar 11, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "view/controlmemberview.h"

/**
 * Initialize the member control gui.
 */
ControlMemberView::ControlMemberView(QWidget *parent) : QWidget(parent) {
    member_list = new ModelListWidget<MemberModel>(this);

    QFormLayout *layout = new QFormLayout(this);
    QVBoxLayout *column = new QVBoxLayout();
    setGeometry(QRect(20, 20, 441, 231));

    layout->setSpacing(6);
    layout->setContentsMargins(11, 11, 11, 11);
    layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    layout->setContentsMargins(0, 0, 0, 0);

    column->setSpacing(0);

    QLabel *help(new QLabel(
        "Select a member from the list\nto toggle the controls"
    ));

    QPushButton *add_button = new QPushButton("Add Member");
    edit_button = new QPushButton("Edit Member");
    mark_button = new QPushButton("Mark Member As Deleted");
    unmark_button = new QPushButton("Un-Mark Member As Deleted");
    del_button = new QPushButton("Delete Member");

    connect(add_button, SIGNAL(clicked()), this, SLOT(addMember()));
    connect(edit_button, SIGNAL(clicked()), this, SLOT(editMember()));
    connect(mark_button, SIGNAL(clicked()), this, SLOT(markMember()));
    connect(unmark_button, SIGNAL(clicked()), this, SLOT(unmarkMember()));
    connect(del_button, SIGNAL(clicked()), this, SLOT(deleteMember()));

    connect(
        member_list, SIGNAL(itemSelectionChanged()),
        this, SLOT(activateButtons())
    );

    if(active_user->hasPermission(ADD_MEMBER)) {
        column->addWidget(add_button);
    }
    if(active_user->hasPermission(EDIT_MEMBER_INFO)) {
        column->addWidget(edit_button);
    }
    if(active_user->hasPermission(EDIT_MEMBER_STATUS)) {
        column->addWidget(mark_button);
    }
    if(active_user->hasPermission(EDIT_MEMBER_STATUS)) {
        column->addWidget(unmark_button);
    }
    if(active_user->hasPermission(DELETE_MEMBER)) {
        column->addWidget(del_button);
    }

    layout->setLayout(0, QFormLayout::FieldRole, column);
    layout->setWidget(0, QFormLayout::LabelRole, member_list);

    populateMembers();

    column->addWidget(help);
}

/*
 * Pupulate the member list and disable some of the member control buttons.
 */
void ControlMemberView::populateMembers() {
    member_list->fill(&MemberModel::findAll);
    mark_button->setDisabled(true);
    unmark_button->setDisabled(true);
    del_button->setDisabled(true);
    edit_button->setDisabled(true);
}

/**
 * Pop up the add member form.
 */
void ControlMemberView::addMember() {
    AddMemberView addMemberDialog(this);
    if(addMemberDialog.exec() == QDialog::Accepted) {
        populateMembers();
    }
}

/**
 * Pop up the edit member form.
 */
void ControlMemberView::editMember() {
    MemberModel *member =  member_list->getModel();
    if(member==0) {
         return;
    }
    EditMemberView editMemberDialog(member,this);
    if(editMemberDialog.exec() == QDialog::Accepted) {
        populateMembers();
    }
}


/**
 * Completely delete a member from the database.
 */
void ControlMemberView::deleteMember() {
    MemberModel *m(member_list->getModel());
    if(0 != m) {
        int ret(QMessageBox::question(this,
            "Please Confirm",
            "Are you sure that you want to delete the member?",
            QMessageBox::Yes,
            QMessageBox::No
        ));
        if(QMessageBox::Yes == ret) {
            m->remove();
            populateMembers();
        }
    }
}

/**
 * Mark a member as deleted.
 */
void ControlMemberView::markMember() {
    MemberModel *m(member_list->getModel());
    if(0 != m) {
        m->markDeleted(true);
        m->save();
        populateMembers();
    }
}

/**
 * Unmark the selected member as marked deleted.
 */
void ControlMemberView::unmarkMember() {
    MemberModel *m(member_list->getModel());
    if(0 != m) {
        m->markDeleted(false);
        m->save();
        populateMembers();
    }
}

/**
 * De/activate the various control buttons depending on the member selected.
 */
void ControlMemberView::activateButtons() {
    MemberModel *member(member_list->getModel());
    if(0 == member) {
        return;
    }

    bool is_marked(member->isMarkedDeleted());

    mark_button->setDisabled(is_marked);
    unmark_button->setDisabled(!is_marked);
    del_button->setDisabled(!is_marked);
    edit_button->setDisabled(false);
}
