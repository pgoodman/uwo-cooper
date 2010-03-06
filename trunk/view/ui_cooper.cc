/*
 * ui_cooper.cc
 *
 *  Created on: Mar 6, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "ui_cooper.h"

/**
 * Constructor, make the UI.
 */
Ui_Cooper::Ui_Cooper(void) {

    Window::setSize(600, 400);
    QLayout *layout(new QGridLayout);
    layout->setSpacing(6);
    layout->setContentsMargins(11, 11, 11, 11);

    member_list = new ModelList<Member>(this);
    committee_list = new ModelList<Committee>(this);

    connect(
        member_list, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
        this, SLOT(activateMemberButtons(QListWidgetItem *, QListWidgetItem *))
    );

    QTabWidget *tabs(new QTabWidget);
    tabs->addTab(makeMemberControls(), "Member");
    tabs->addTab(makeCommitteeControls(), "Committee");
    makeMenuBar();

    layout->addWidget(tabs);

    setLayout(layout);
}

/**
 * Create the member controls.
 */
QWidget *Ui_Cooper::makeMemberControls(void) {

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

    if(User::canDo(ADD_MEMBER)) column->addWidget(add_button);
    if(User::canDo(EDIT_MEMBER_INFO)) column->addWidget(edit_button);
    if(User::canDo(EDIT_MEMBER_STATUS)) column->addWidget(mark_button);
    if(User::canDo(EDIT_MEMBER_STATUS)) column->addWidget(unmark_button);
    if(User::canDo(DELETE_MEMBER)) column->addWidget(del_button);

    layout->setLayout(0, QFormLayout::FieldRole, column);
    layout->setWidget(0, QFormLayout::LabelRole, member_list);

    populateMembers();

    column->addWidget(help);


    return controls;
}

/**
 * Create the committee controls.
 */
QWidget *Ui_Cooper::makeCommitteeControls(void) {
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
void Ui_Cooper::makeMenuBar(void) {

    QMenuBar *menuBar = new QMenuBar();
    menuBar->setGeometry(QRect(0, 0, 600, 21));
    QMenu *menuSystem = new QMenu(menuBar);
    QMenu *menuTask = new QMenu("Task", menuBar);
    QMenu *menuEvent = new QMenu("Event", menuBar);
    QMenu *menuPrint = new QMenu("Print", menuBar);
    QMenu *menuHelp = new QMenu("Help", menuBar);

    menuBar->addAction(menuSystem->menuAction());
    menuBar->addAction(menuTask->menuAction());
    menuBar->addAction(menuEvent->menuAction());
    menuBar->addAction(menuPrint->menuAction());
    menuBar->addAction(menuHelp->menuAction());

    QAction *actionLogoff = Window::action();
    QAction *actionQuit = Window::action();

    menuSystem->addAction(actionLogoff);
    menuSystem->addAction(actionQuit);

    /*
    menuTask->addAction(actionAssign_Task);
    menuTask->addAction(actionEdit_Task);
    menuTask->addAction(actionDelete_Task);

    menuEvent->addAction(actionMove_Out);
    menuEvent->addAction(actionInternal_Move);
    menuEvent->addAction(actionAnnual_Task_Spec);
    menuPrint->addAction(actionPhone_List);
    menuPrint->addAction(actionCommittee_List);
    menuPrint->addAction(actionTask_List);

    menuHelp->addAction(actionManual);
    menuHelp->addAction(actionAbout_Cooper);
    */

    Window::setMenuBar(menuBar);
}

/*
 * Pupulate the member list and disable some buttons.
 */
void Ui_Cooper::populateMembers() {
    member_list->fill(&Member::findAll);
    mark_button->setDisabled(true);
    unmark_button->setDisabled(true);
    del_button->setDisabled(true);
    edit_button->setDisabled(true);
}

void Ui_Cooper::populateCommittees() {
    committee_list->fill(&Committee::findAll);
}

void Ui_Cooper::addMember() {
    Ui_AddMember* addMemberDialog = new Ui_AddMember;
    addMemberDialog->show();
    if(addMemberDialog->exec() == QDialog::Accepted) {
        populateMembers();
    }
    delete addMemberDialog;
}

void Ui_Cooper::editMember() {
    Ui_AddMember* editMemberDialog = new Ui_AddMember;
    editMemberDialog->show();
    editMemberDialog->setWindowTitle("Edit Member Information");
    editMemberDialog->layout->removeWidget(editMemberDialog->addNewButton);
    delete editMemberDialog->addNewButton;
    QPushButton *saveButton = new QPushButton(QString::fromUtf8("Save Changes"));
    editMemberDialog->layout->addWidget(saveButton,11,1,1,1);
    connect(saveButton,SIGNAL(clicked()),this,SLOT(saveChanges()));
    QPushButton *resetButton = new QPushButton(QString::fromUtf8("Reset"));
    editMemberDialog->layout->addWidget(resetButton,11,3,1,1);
    connect(resetButton,SIGNAL(clicked()),this,SLOT(resetChanges()));

    fillEditForm(editMemberDialog);

    if(editMemberDialog->exec() == QDialog::Accepted)
    {
          populateMembers();
    }

    delete editMemberDialog;
}

void Ui_Cooper::saveChanges(){

}
void Ui_Cooper::resetChanges(){

}
void Ui_Cooper::fillEditForm(Ui_AddMember* editMemberDialog){
    Member *selectedMember =  member_list->getModel();
    if(!selectedMember==0){
        editMemberDialog->LastNameEdit->setText(selectedMember->getLastName());
        editMemberDialog->GivenNameEdit->setText(selectedMember->getFirstName());
        double _m=selectedMember->getMoneyOwed();
        if(_m!=0) {
            QString _mStr;
            editMemberDialog->ArrearYesButton->setChecked(true);
            editMemberDialog->ArrearsAmountEdit->setText(_mStr.setNum(_m));
        }
        else {
            editMemberDialog->ArrearYesButton->setChecked(false);
            editMemberDialog->ArrearsAmountEdit->setText("");
        }
        editMemberDialog->PrivateNoButton->setChecked(selectedMember->isTelephoneShared());
        editMemberDialog->PasswordEdit->setText(selectedMember->getPassword());
        editMemberDialog->NumberEdit->setText(selectedMember->getTelephoneNum());
        time_t _t = selectedMember->getMoveInTime();
        time(&_t);
        QString _qt;
        _qt.fromStdString(ctime(&_t));
        editMemberDialog->lineEdit->setText(_qt);
        editMemberDialog->UserIDEdit->setText(selectedMember->getLoginName());
        if(!selectedMember->getCommittee()==0){
            editMemberDialog->CommitteeYesButton->setChecked(true);
            //assume committee name is unique. otherwise, have to go through all matched items
            int _id = selectedMember->getCommitteeID();
            Committee *_committee = Committee::load(_id);
            QListWidgetItem * _qli =editMemberDialog->committee_list->findItems(_committee->toString(),Qt::MatchExactly)[0];
            _qli->setSelected(true);
            _qli->setBackgroundColor(Qt::red);
        }
        else
            editMemberDialog->CommitteeYesButton->setChecked(false);

    }
}
void Ui_Cooper::deleteMember() {
    Member *m(member_list->getModel());
    if(0 != m) {
        m->hardDelete();
        populateMembers();
    }
}

void Ui_Cooper::markMember() {
    Member *m(member_list->getModel());
    if(0 != m) {
        m->softDelete(true);
        populateMembers();
    }
}

void Ui_Cooper::unmarkMember() {
    Member *m(member_list->getModel());
    if(0 != m) {
        m->softDelete(false);
        populateMembers();
    }
}

void Ui_Cooper::activateMemberButtons(QListWidgetItem *old,
                                      QListWidgetItem *curr) {
    (void) old; (void) curr;

    Member *member(member_list->getModel());
    if(0 == member) {
        return;
    }

    bool is_marked(member->isSoftDeleted());

    mark_button->setDisabled(is_marked);
    unmark_button->setDisabled(!is_marked);
    del_button->setDisabled(!is_marked);
    edit_button->setDisabled(false);
}
