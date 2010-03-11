/*
 * ui_cooper.cc
 *
 *  Created on: Mar 6, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "view/homeview.h"

/**
 * Constructor, make the UI.
 */
HomeView::HomeView(void) {
    member_list = new ModelListWidget<MemberModel>(this);
    committee_list = new ModelListWidget<CommitteeModel>(this);

    connect(
        member_list,
        SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
        this,
        SLOT(activateMemberButtons(QListWidgetItem *, QListWidgetItem *))
    );

    QTabWidget *tabs(new QTabWidget);
    tabs->addTab(makeMemberControls(), "Member");
    tabs->addTab(makeCommitteeControls(), "Committee");
    makeMenuBar();

    setContentsMargins(11, 11, 11, 11);
    setCentralWidget(tabs);
}

/**
 * Create the member controls.
 */
QWidget *HomeView::makeMemberControls(void) {

    QWidget *controls = new QWidget;
    QFormLayout *layout = new QFormLayout(controls);
    QVBoxLayout *column = new QVBoxLayout();
    controls->setGeometry(QRect(20, 20, 441, 231));

    layout->setSpacing(6);
    layout->setContentsMargins(11, 11, 11, 11);
    layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    layout->setContentsMargins(0, 0, 0, 0);

    column->setSpacing(0);

    QLabel *help(new QLabel(
        "Select a member from the list\nto toggle the controls"
    ));

    QPushButton *add_button = new QPushButton("Add Member", controls);
    edit_button = new QPushButton("Edit Member", controls);

    mark_button = new QPushButton(
        "Mark Member As Deleted", controls
    );
    unmark_button = new QPushButton(
        "Un-Mark Member As Deleted", controls
    );
    del_button = new QPushButton("Delete Member", controls);

    connect(add_button, SIGNAL(clicked()), this, SLOT(addMember()));
    connect(edit_button, SIGNAL(clicked()), this, SLOT(editMember()));
    connect(mark_button, SIGNAL(clicked()), this, SLOT(markMember()));
    connect(unmark_button, SIGNAL(clicked()), this, SLOT(unmarkMember()));
    connect(del_button, SIGNAL(clicked()), this, SLOT(deleteMember()));

    if(UserModel::canDo(ADD_MEMBER)) column->addWidget(add_button);
    if(UserModel::canDo(EDIT_MEMBER_INFO)) column->addWidget(edit_button);
    if(UserModel::canDo(EDIT_MEMBER_STATUS)) column->addWidget(mark_button);
    if(UserModel::canDo(EDIT_MEMBER_STATUS)) column->addWidget(unmark_button);
    if(UserModel::canDo(DELETE_MEMBER)) column->addWidget(del_button);

    layout->setLayout(0, QFormLayout::FieldRole, column);
    layout->setWidget(0, QFormLayout::LabelRole, member_list);

    populateMembers();

    column->addWidget(help);


    return controls;
}

/**
 * Create the committee controls.
 */
QWidget *HomeView::makeCommitteeControls(void) {
    QWidget *controls = new QWidget;
    QFormLayout *layout = new QFormLayout(controls);
    QVBoxLayout *column = new QVBoxLayout();

    controls->setGeometry(QRect(20, 20, 441, 231));

    layout->setSpacing(6);
    layout->setContentsMargins(11, 11, 11, 11);
    layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    layout->setContentsMargins(0, 0, 0, 0);

    column->setSpacing(0);

    QPushButton *add_button = new QPushButton("Add Committee", controls);
    QPushButton *edit_button = new QPushButton("Edit Committee", controls);
    QPushButton *del_button = new QPushButton("Delete Committee", controls);

    connect(add_button, SIGNAL(clicked()), this, SLOT(addCommittee()));
    connect(edit_button, SIGNAL(clicked()), this, SLOT(editCommittee()));
    connect(del_button, SIGNAL(clicked()), this, SLOT(deleteCommittee()));

    column->addWidget(add_button);
    column->addWidget(edit_button);
    column->addWidget(del_button);

    layout->setLayout(0, QFormLayout::FieldRole, column);
    layout->setWidget(0, QFormLayout::LabelRole, committee_list);

    populateCommittees();

    return controls;
}

/**
 * Create the menu bar.
 */
void HomeView::makeMenuBar(void) {
    QMenu *file_menu = menuBar()->addMenu("&File");
    (void) file_menu;
}

/**
 * Close evebt for the home window.
 */
void HomeView::closeEvent(QCloseEvent *event) {
    Database::disconnect();
    QMainWindow::closeEvent(event);
}

/*
 * Pupulate the member list and disable some buttons.
 */
void HomeView::populateMembers() {
    member_list->fill(&MemberModel::findAll);
    mark_button->setDisabled(true);
    unmark_button->setDisabled(true);
    del_button->setDisabled(true);
    edit_button->setDisabled(true);
}

void HomeView::populateCommittees() {
    committee_list->fill(&CommitteeModel::findAll);
}

void HomeView::addMember() {
    AddMemberView *addMemberDialog = new AddMemberView;
    addMemberDialog->show();
    if(addMemberDialog->exec() == QDialog::Accepted) {
        populateMembers();
    }
    delete addMemberDialog;
}

void HomeView::editMember() {
#if 0
    MemberModel *member =  member_list->getModel();
    if(member==0) {
         return;
    }

    AddMemberView *editMemberDialog = new AddMemberView;
    editMemberDialog->show();

    editMemberDialog->setWindowTitle("Edit Member Information");

    editMemberDialog->layout->removeWidget(editMemberDialog->addNewButton);
    delete editMemberDialog->addNewButton;

    QPushButton *saveButton = new QPushButton(QString::fromUtf8("Save Changes"));
    editMemberDialog->layout->addWidget(saveButton,11,0,1,1);
    connect(saveButton,SIGNAL(clicked()),editMemberDialog,SLOT(saveChanges()));

    QPushButton *resetButton = new QPushButton(QString::fromUtf8("Reset"));
    editMemberDialog->layout->addWidget(resetButton,11,1,1,1);
    connect(resetButton,SIGNAL(clicked()),editMemberDialog,SLOT(resetChanges()));

    editMemberDialog->setSelectedMember(member);
    editMemberDialog->fillEditForm();

    if(editMemberDialog->exec() == QDialog::Accepted)
    {
        populateMembers();
    }

    delete editMemberDialog;
#endif
}

void HomeView::deleteMember() {
    MemberModel *m(member_list->getModel());
    if(0 != m) {
        m->remove();
        populateMembers();
    }
}

void HomeView::markMember() {
    MemberModel *m(member_list->getModel());
    if(0 != m) {
        m->markDeleted(true);
        m->save();
        populateMembers();
    }
}

void HomeView::unmarkMember() {
    MemberModel *m(member_list->getModel());
    if(0 != m) {
        m->markDeleted(false);
        m->save();
        populateMembers();
    }
}

void HomeView::activateMemberButtons(QListWidgetItem *old,
                                     QListWidgetItem *curr) {
    (void) old; (void) curr;

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
