
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

class MemberList : public ModelList<Member> {
    Q_OBJECT
public:
    MemberList(QWidget *w) : ModelList<Member>(w) { }
};

class CommitteeList : public ModelList<Committee> {
    Q_OBJECT
public:
    CommitteeList(QWidget *w) : ModelList<Committee>(w) { }
};

class Ui_Cooper : public QWidget
{
Q_OBJECT

    MemberList *member_list;
    CommitteeList *committee_list;

public:

    Ui_Cooper(void) {
        Window::setSize(600, 400);
        QLayout *layout(new QGridLayout);
        layout->setSpacing(6);
        layout->setContentsMargins(11, 11, 11, 11);

        member_list = new MemberList(this);
        committee_list = new CommitteeList(this);

        QTabWidget *tabs(new QTabWidget);
        tabs->addTab(makeMemberControls(), "Member");
        tabs->addTab(makeCommitteeControls(), "Committee");

        layout->addWidget(tabs);

        setLayout(layout);
    }

private:

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
        QPushButton *mark_button = new QPushButton(
            "Mark Member As Deleted", controls
        );
        QPushButton *del_button = new QPushButton("Delete Member", controls);

        connect(add_button, SIGNAL(clicked()), this, SLOT(addMember()));
        connect(edit_button, SIGNAL(clicked()), this, SLOT(editMember()));
        connect(mark_button, SIGNAL(clicked()), this, SLOT(markMember()));
        connect(del_button, SIGNAL(clicked()), this, SLOT(deleteMember()));

        if(User::canDo(ADD_MEMBER)) column->addWidget(add_button);
        if(User::canDo(EDIT_MEMBER_INFO)) column->addWidget(edit_button);
        if(User::canDo(EDIT_MEMBER_STATUS)) column->addWidget(mark_button);
        if(User::canDo(DELETE_MEMBER)) column->addWidget(del_button);

        mark_button->setDisabled(true);
        del_button->setDisabled(true);

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
        cout << "delete member." << endl;
        Member *m = member_list->getModel();
        if(0 != m) {
            m->hardDelete();
            populateMembers();
        }
    }
    void markMember() {
        cout << "mark member." << endl;
        //Member *m = member_list->getModel();
        //m->softDelete(!m->isSoftDeleted());
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

    void populateMembers() {
        member_list->fill(&Member::findAll);
    }
    void populateCommittees() {
        committee_list->fill(&Committee::findAll);
    }
};


#endif // UI_COOPER_H
