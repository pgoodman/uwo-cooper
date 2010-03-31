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

    QGridLayout *layout = new QGridLayout(this);
    QVBoxLayout *column = new QVBoxLayout;

    setGeometry(QRect(20, 20, 441, 231));

    layout->setSpacing(6);
    layout->setContentsMargins(11, 11, 11, 11);

    column->setSpacing(0);

    QPushButton *add_button = new QPushButton("Add Member");
    edit_button = new QPushButton("Edit Member");
    mark_button = new QPushButton("Mark Member As Deleted");
    unmark_button = new QPushButton("Un-Mark Member As Deleted");
    del_button = new QPushButton("Delete Member");
    move_out_button = new QPushButton("Trigger Move Out Event");
    internal_move_button = new QPushButton("Trigger Internal Move Event");
    dependant_button = new QPushButton("Manage Dependants");
    print_public_button = new QPushButton("Print Public Phone List");
    print_private_button = new QPushButton("Print Full Phone List");

    connect(add_button, SIGNAL(clicked()), this, SLOT(addMember()));
    connect(edit_button, SIGNAL(clicked()), this, SLOT(editMember()));
    connect(mark_button, SIGNAL(clicked()), this, SLOT(markMember()));
    connect(unmark_button, SIGNAL(clicked()), this, SLOT(unmarkMember()));
    connect(del_button, SIGNAL(clicked()), this, SLOT(deleteMember()));
    connect(move_out_button, SIGNAL(clicked()), this, SLOT(triggerMoveOut()));
    connect(internal_move_button, SIGNAL(clicked()), this, SLOT(triggerInternalMove()));
    connect(dependant_button, SIGNAL(clicked()), this, SLOT(manageDependants()));
    connect(print_public_button, SIGNAL(clicked()), this, SLOT(printPublic()));
    connect(print_private_button, SIGNAL(clicked()), this, SLOT(printPrivate()));

    connect(
        member_list, SIGNAL(itemSelectionChanged()),
        this, SLOT(activateButtons())
    );

    if(active_user->hasPermission(ADD_MEMBER)) {
        column->addWidget(add_button);
    }

    if(active_user->hasPermission(EDIT_SELF_PASS)) {
            column->addWidget(edit_button);
    }

    if(active_user->hasPermission(EDIT_MEMBER_INFO)) {
        column->addWidget(dependant_button);
        column->addWidget(move_out_button);
        column->addWidget(internal_move_button);
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

    column->addWidget(print_public_button);

    if(active_user->hasPermission(PRINT_PRIVATE_LIST)) {
       column->addWidget(print_private_button);
    }

    layout->addWidget(
        new QLabel("Select a member from the list to toggle the controls"),
        1, 1, 1, 2
    );
    layout->addWidget(member_list, 2, 1, 1, 1);
    layout->addLayout(column, 2, 2, 1, 1);

    populateMembers();
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
    dependant_button->setDisabled(true);
    move_out_button->setDisabled(true);
    internal_move_button->setDisabled(true);
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

    if(!active_user->is_coordinator) {
        MemberModel *curmember;
        curmember = static_cast<MemberModel *>(active_user);
        if(!curmember->hasPermission(EDIT_MEMBER_INFO) && !curmember->hasPermission(VIEW_OTHER_INFO)) {
            if(curmember->getMemberId() == member->getMemberId()) {
                edit_button->setDisabled(false);
            }else {
                edit_button->setDisabled(true);
            }
            return;
        }
    }
    mark_button->setDisabled(is_marked);
    unmark_button->setDisabled(!is_marked);
    del_button->setDisabled(!is_marked);
    edit_button->setDisabled(false);
    dependant_button->setDisabled(false);
    move_out_button->setDisabled(false);
    internal_move_button->setDisabled(false);
}

/**
 * Launch the dialog to manage a move out event.
 */
void ControlMemberView::triggerMoveOut() {
    MemberModel *member(member_list->getModel());
    if (0 == member) {
        return;
    }

    TriggerMoveOutView moveOutDialog(member,this);
    moveOutDialog.exec();
}

/**
 * Launch the dialog to manage an internal move event.
 */
void ControlMemberView::triggerInternalMove() {
    MemberModel *member(member_list->getModel());
    if (0 == member) {
        return;
    }

    TriggerInternalMoveView internalMoveDialog(member, this);
    internalMoveDialog.exec();
}

/**
 * Launch the dialog to manage a member's dependants.
 */
void ControlMemberView::manageDependants(void) {
    MemberModel *member(member_list->getModel());
    if (0 == member) {
        return;
    }
    DependantListView dep(member, this);
    dep.exec();
}

void ControlMemberView::printPublic(){
    new PrintController(PHONE_LIST_PUBLIC);
}

void ControlMemberView::printPrivate(){
    new PrintController(PHONE_LIST_ALL);
}
