
#ifndef UI_COOPER_H
#define UI_COOPER_H

#include <Qt>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QFormLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QtGui>
#include <QListWidget>
#include <QListWidgetItem>

#include "datatype/user.h"
#include "datatype/member.h"
#include "datatype/permission.h"
#include "cooperdb.h"
#include "ui_addmember.h"

#include "modellist.h"
#include "modellistitem.h"

#include "window.h"

class Ui_Cooper : public QWidget
{
Q_OBJECT

    ModelList<Member> *member_list;
    ModelList<Committee> *committee_list;

public:

    Ui_Cooper(void) {
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

        layout->addWidget(tabs);

        setLayout(layout);
    }

private:

    QPushButton *mark_button;
    QPushButton *unmark_button;
    QPushButton *del_button;

    /**
     * Create the member controls.
     */
    QWidget *makeMemberControls(void) {
        QWidget *controls = new QWidget;
        QFormLayout *layout = new QFormLayout(controls);
        QVBoxLayout *column = new QVBoxLayout();
        addMemberDialog = new Ui_AddMember;

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
        QPushButton *edit_button = new QPushButton("Edit Member", controls);

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
    QWidget *makeCommitteeControls(void) {
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
    void makeMenuBar(void) {
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

    Ui_AddMember* addMemberDialog;
    Ui_AddMember* editMemberDialog;

    void populateMembers() {
        member_list->fill(&Member::findAll);
        mark_button->setDisabled(true);
        unmark_button->setDisabled(true);
        del_button->setDisabled(true);
    }
    void populateCommittees() {
        committee_list->fill(&Committee::findAll);
    }

public slots:
    void addMember() {
        addMemberDialog->show();

        if(addMemberDialog->exec() == QDialog::Accepted) {
            populateMembers();
        }

        cout << "show add member form." << endl;
    }
    void editMember() {
        editMemberDialog->show();
        //editMemberDialog->setWindowTitle("Edit Member Information");
       // editMemberDialog->addNewButton->setText("Save Changes");
      //  QPushButton *resetButton = new QPushButton(QString::fromUtf8("Reset"));
      //  editMemberDialog->layout->addWidget(resetButton,11,3,1,1);
      //  Member *selectedMember = member_list->getModel();

        if(editMemberDialog->exec() == QDialog::Accepted)
        {
             member_list->fill(&Member::findAll);
        }

        cout << "show edit member form." << endl;


    }

    void deleteMember() {
        member_list->getModel()->hardDelete();
        populateMembers();
    }
    void markMember() {
        member_list->getModel()->softDelete(true);
        populateMembers();
    }
    void unmarkMember() {
        member_list->getModel()->softDelete(false);
        populateMembers();
    }
    void editCommittee() {
        cout << "show edit committee form." << endl;
    }
    void addCommittee() {
        cout << "show add committee form." << endl;
    }
    void deleteCommittee() {
        cout << "show delete committee form." << endl;
    }
    void viewCommittee() {
        cout << "show view committee." << endl;
    }

    /**
     * Change the buttons depending on whether or not members have a certain
     * status.
     */
    void activateMemberButtons(QListWidgetItem *old, QListWidgetItem *curr) {
        (void) old; (void) curr;

        Member *member(member_list->getModel());
        if(0 == member) {
            return;
        }

        bool is_marked(member->isSoftDeleted());

        mark_button->setDisabled(is_marked);
        unmark_button->setDisabled(!is_marked);
        del_button->setDisabled(!is_marked);
    }
};


#endif // UI_COOPER_H
