/********************************************************************************
** Form generated from reading UI file 'cooperXs2808.ui'
**
** Created: Thu Mar 4 12:02:16 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

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
#include <QTextEdit>
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

#include "datatype/member.h"
#include "cooperdb.h"
#include "ui_addmember.h"

#include "modellist.h"
#include "modellistitem.h"

class MemberList : public ModelList<Member> {
    Q_OBJECT
public:
    MemberList(QWidget *w) : ModelList<Member>(w) { }
};

class Ui_Cooper : public QObject
{
Q_OBJECT
public:
 //   Ui_AddMember *addDialog;
    QAction *actionLogoff;
    QAction *actionQuit;
    QAction *actionAdd_Committee;
    QAction *actionDelete_Committee;
    QAction *actionAssign_Task;
    QAction *actionEdit_Task;
    QAction *actionDelete_Task;
    QAction *actionMove_Out;
    QAction *actionInternal_Move;
    QAction *actionAnnual_Task_Spec;
    QAction *actionPhone_List;
    QAction *actionCommittee_List;
    QAction *actionTask_List;
    QAction *actionManual;
    QAction *actionAbout_Cooper;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *memberTab;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *actionAdd_Member_2;
    QPushButton *actionEdit_Member;
    QPushButton *actionDelete_Member;
    MemberList *memberList;
    QWidget *committeeTab;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout;
    QTextEdit *committeeList;
    QVBoxLayout *verticalLayout_2;
    QPushButton *viewCommittee;
    QPushButton *addCommittee;
    QPushButton *deleteCommittee;
    QMenuBar *menuBar;
    QMenu *menuSystem;
    QMenu *menuTask;
    QMenu *menuEvent;
    QMenu *menuPrint;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Cooper)
    {
        //QString objectName = "addMember";
        addMember = new Ui_AddMember;
        if (Cooper->objectName().isEmpty())
            Cooper->setObjectName(QString::fromUtf8("Cooper"));

        Cooper->resize(600, 400);
        actionLogoff = new QAction(Cooper);
        actionLogoff->setObjectName(QString::fromUtf8("actionLogoff"));
        actionQuit = new QAction(Cooper);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionAdd_Committee = new QAction(Cooper);
        actionAdd_Committee->setObjectName(QString::fromUtf8("actionAdd_Committee"));
        actionDelete_Committee = new QAction(Cooper);
        actionDelete_Committee->setObjectName(QString::fromUtf8("actionDelete_Committee"));
        actionAssign_Task = new QAction(Cooper);
        actionAssign_Task->setObjectName(QString::fromUtf8("actionAssign_Task"));
        actionEdit_Task = new QAction(Cooper);
        actionEdit_Task->setObjectName(QString::fromUtf8("actionEdit_Task"));
        actionDelete_Task = new QAction(Cooper);
        actionDelete_Task->setObjectName(QString::fromUtf8("actionDelete_Task"));
        actionMove_Out = new QAction(Cooper);
        actionMove_Out->setObjectName(QString::fromUtf8("actionMove_Out"));
        actionInternal_Move = new QAction(Cooper);
        actionInternal_Move->setObjectName(QString::fromUtf8("actionInternal_Move"));
        actionAnnual_Task_Spec = new QAction(Cooper);
        actionAnnual_Task_Spec->setObjectName(QString::fromUtf8("actionAnnual_Task_Spec"));
        actionPhone_List = new QAction(Cooper);
        actionPhone_List->setObjectName(QString::fromUtf8("actionPhone_List"));
        actionCommittee_List = new QAction(Cooper);
        actionCommittee_List->setObjectName(QString::fromUtf8("actionCommittee_List"));
        actionTask_List = new QAction(Cooper);
        actionTask_List->setObjectName(QString::fromUtf8("actionTask_List"));
        actionManual = new QAction(Cooper);
        actionManual->setObjectName(QString::fromUtf8("actionManual"));
        actionAbout_Cooper = new QAction(Cooper);
        actionAbout_Cooper->setObjectName(QString::fromUtf8("actionAbout_Cooper"));
        centralWidget = new QWidget(Cooper);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 601, 331));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(gridLayoutWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        memberTab = new QWidget();
        memberTab->setObjectName(QString::fromUtf8("memberTab"));
        formLayoutWidget = new QWidget(memberTab);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(20, 20, 441, 231));
        formLayout_2 = new QFormLayout(formLayoutWidget);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        actionAdd_Member_2 = new QPushButton(formLayoutWidget);
        actionAdd_Member_2->setObjectName(QString::fromUtf8("actionAdd_Member_2"));
        connect(actionAdd_Member_2, SIGNAL(clicked()), this, SLOT(on_actionAdd_Member_triggered()));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(actionAdd_Member_2->sizePolicy().hasHeightForWidth());
        actionAdd_Member_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(actionAdd_Member_2);

        actionEdit_Member = new QPushButton(formLayoutWidget);
        actionEdit_Member->setObjectName(QString::fromUtf8("actionEdit_Member"));
        connect(actionEdit_Member, SIGNAL(clicked()), this, SLOT(on_actionEdit_Member_triggered()));
        verticalLayout->addWidget(actionEdit_Member);

        actionDelete_Member = new QPushButton(formLayoutWidget);
        actionDelete_Member->setObjectName(QString::fromUtf8("actionDelete_Member"));
        connect(actionDelete_Member, SIGNAL(clicked()), this, SLOT(on_actionDelete_Member_triggered()));
        verticalLayout->addWidget(actionDelete_Member);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, verticalLayout);

        memberList = new MemberList(formLayoutWidget);
        memberList->setObjectName(QString::fromUtf8("memberList"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, memberList);

        tabWidget->addTab(memberTab, QString());
        committeeTab = new QWidget();
        committeeTab->setObjectName(QString::fromUtf8("committeeTab"));
        formLayoutWidget_2 = new QWidget(committeeTab);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(10, 10, 461, 191));
        formLayout = new QFormLayout(formLayoutWidget_2);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        committeeList = new QTextEdit(formLayoutWidget_2);
        committeeList->setObjectName(QString::fromUtf8("committeeList"));

        formLayout->setWidget(0, QFormLayout::LabelRole, committeeList);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        viewCommittee = new QPushButton(formLayoutWidget_2);
        viewCommittee->setObjectName(QString::fromUtf8("viewCommittee"));
        connect(viewCommittee, SIGNAL(clicked()), this, SLOT(on_actionView_Committee_triggered()));

        verticalLayout_2->addWidget(viewCommittee);

        addCommittee = new QPushButton(formLayoutWidget_2);
        addCommittee->setObjectName(QString::fromUtf8("addCommittee"));
        connect(addCommittee, SIGNAL(clicked()), this, SLOT(on_actionAdd_Committee_triggered()));

        verticalLayout_2->addWidget(addCommittee);

        deleteCommittee = new QPushButton(formLayoutWidget_2);
        deleteCommittee->setObjectName(QString::fromUtf8("deleteCommittee"));
        connect(deleteCommittee, SIGNAL(clicked()), this, SLOT(on_actionDelete_Committee_triggered()));

        verticalLayout_2->addWidget(deleteCommittee);


        formLayout->setLayout(0, QFormLayout::FieldRole, verticalLayout_2);

        tabWidget->addTab(committeeTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        Cooper->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Cooper);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuSystem = new QMenu(menuBar);
        menuSystem->setObjectName(QString::fromUtf8("menuSystem"));
        menuTask = new QMenu(menuBar);
        menuTask->setObjectName(QString::fromUtf8("menuTask"));
        menuEvent = new QMenu(menuBar);
        menuEvent->setObjectName(QString::fromUtf8("menuEvent"));
        menuPrint = new QMenu(menuBar);
        menuPrint->setObjectName(QString::fromUtf8("menuPrint"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        Cooper->setMenuBar(menuBar);
        statusBar = new QStatusBar(Cooper);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Cooper->setStatusBar(statusBar);

        menuBar->addAction(menuSystem->menuAction());
        menuBar->addAction(menuTask->menuAction());
        menuBar->addAction(menuEvent->menuAction());
        menuBar->addAction(menuPrint->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuSystem->addAction(actionLogoff);
        menuSystem->addAction(actionQuit);
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


        populateMembers();

        retranslateUi(Cooper);
        QObject::connect(actionQuit, SIGNAL(triggered()), Cooper, SLOT(close()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Cooper);
    } // setupUi

    void retranslateUi(QMainWindow *Cooper)
    {
        Cooper->setWindowTitle(QApplication::translate("Cooper", "Cooper", 0, QApplication::UnicodeUTF8));
        actionLogoff->setText(QApplication::translate("Cooper", "Logoff", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("Cooper", "Quit", 0, QApplication::UnicodeUTF8));
        actionAdd_Committee->setText(QApplication::translate("Cooper", "Add Committee", 0, QApplication::UnicodeUTF8));
        actionDelete_Committee->setText(QApplication::translate("Cooper", "Delete Committee", 0, QApplication::UnicodeUTF8));
        actionAssign_Task->setText(QApplication::translate("Cooper", "Assign Task", 0, QApplication::UnicodeUTF8));
        actionEdit_Task->setText(QApplication::translate("Cooper", "Edit Task", 0, QApplication::UnicodeUTF8));
        actionDelete_Task->setText(QApplication::translate("Cooper", "Delete Task", 0, QApplication::UnicodeUTF8));
        actionMove_Out->setText(QApplication::translate("Cooper", "Move Out", 0, QApplication::UnicodeUTF8));
        actionInternal_Move->setText(QApplication::translate("Cooper", "Internal Move", 0, QApplication::UnicodeUTF8));
        actionAnnual_Task_Spec->setText(QApplication::translate("Cooper", "Annual Task Spec", 0, QApplication::UnicodeUTF8));
        actionPhone_List->setText(QApplication::translate("Cooper", "Phone List", 0, QApplication::UnicodeUTF8));
        actionCommittee_List->setText(QApplication::translate("Cooper", "Committee List", 0, QApplication::UnicodeUTF8));
        actionTask_List->setText(QApplication::translate("Cooper", "Task List", 0, QApplication::UnicodeUTF8));
        actionManual->setText(QApplication::translate("Cooper", "Manual", 0, QApplication::UnicodeUTF8));
        actionAbout_Cooper->setText(QApplication::translate("Cooper", "About Cooper", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAdd_Member_2->setToolTip(QApplication::translate("Cooper", "Add Member", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAdd_Member_2->setText(QApplication::translate("Cooper", "Add Member", 0, QApplication::UnicodeUTF8));
        actionEdit_Member->setText(QApplication::translate("Cooper", "Edit Member", 0, QApplication::UnicodeUTF8));
        actionDelete_Member->setText(QApplication::translate("Cooper", "Delete Member", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(memberTab), QApplication::translate("Cooper", "Member", 0, QApplication::UnicodeUTF8));
        viewCommittee->setText(QApplication::translate("Cooper", "View Committee", 0, QApplication::UnicodeUTF8));
        addCommittee->setText(QApplication::translate("Cooper", "Add Committee", 0, QApplication::UnicodeUTF8));
        deleteCommittee->setText(QApplication::translate("Cooper", "Delete Committee", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(committeeTab), QApplication::translate("Cooper", "Committee", 0, QApplication::UnicodeUTF8));
        menuSystem->setTitle(QApplication::translate("Cooper", "System", 0, QApplication::UnicodeUTF8));
        menuTask->setTitle(QApplication::translate("Cooper", "Task", 0, QApplication::UnicodeUTF8));
        menuEvent->setTitle(QApplication::translate("Cooper", "Event", 0, QApplication::UnicodeUTF8));
        menuPrint->setTitle(QApplication::translate("Cooper", "Print", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("Cooper", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi
    /*
    class MemberListItem : public QListWidgetItem {
    public:
        const Member *user;
        MemberListItem(QListWidget *parent, Member *member)
        : QListWidgetItem(parent), user(member) {
            setData(Qt::DisplayRole, (QString) member);
        }
    };*/
    /*
    class MemberList : public QListWidget {

    };*/

void populateMembers()
{
    //pair<Member::iterator, Member::iterator> its(Member::findAll());
    //int i(0);
    /*for(Member::iterator it(its.first); it != its.second; it++) {
        memberList->insertItem(
            i++,
            new MemberListItem(memberList, *it)
        );

        //memberList->insertItem
       //cursor = textEdit->textCursor();
       //cursor.movePosition(QTextCursor::StartOfWord);
       //cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

       //textEdit->setText(cursor.selectedText() + (*it)->getFullName());
    }*/

    pair<Member::iterator, Member::iterator> its(Member::findAll());
    memberList->fill(its);

}

public slots:
void on_actionAdd_Member_triggered()
{
    addMember->show();

    if(addMember->exec() == QDialog::Accepted)
    {
        populateMembers();
    }
}
    void on_actionEdit_Member_triggered(){return;}
    void on_actionDelete_Member_triggered(){return;}
    void on_actionEdit_Committee_triggered(){return;}
    void on_actionAdd_Committee_triggered(){return;}
    void on_actionDelete_Committee_triggered(){return;}
    void on_actionView_Committee_triggered(){return;}

private:
    Ui_AddMember *addMember;
};
/*
namespace Ui {
    class Cooper: public Ui_Cooper {};
} // namespace Ui*/


#endif // UI_COOPER_H
