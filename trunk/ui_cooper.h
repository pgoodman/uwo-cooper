/********************************************************************************
** Form generated from reading UI file 'cooper.ui'
**
** Created: Tue Feb 16 15:25:56 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COOPER_H
#define UI_COOPER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cooper
{
public:
    QAction *actionLogoff;
    QAction *actionQuit;
    QAction *actionAdd_Member;
    QAction *actionEdit_Member;
    QAction *actionDelete_Member;
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
    QMenuBar *menuBar;
    QMenu *menuSystem;
    QMenu *menuMember;
    QMenu *menuCommittee;
    QMenu *menuTask;
    QMenu *menuEvent;
    QMenu *menuPrint;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Cooper)
    {
        if (Cooper->objectName().isEmpty())
            Cooper->setObjectName(QString::fromUtf8("Cooper"));
        Cooper->resize(600, 400);
        actionLogoff = new QAction(Cooper);
        actionLogoff->setObjectName(QString::fromUtf8("actionLogoff"));
        actionQuit = new QAction(Cooper);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionAdd_Member = new QAction(Cooper);
        actionAdd_Member->setObjectName(QString::fromUtf8("actionAdd_Member"));
        actionEdit_Member = new QAction(Cooper);
        actionEdit_Member->setObjectName(QString::fromUtf8("actionEdit_Member"));
        actionDelete_Member = new QAction(Cooper);
        actionDelete_Member->setObjectName(QString::fromUtf8("actionDelete_Member"));
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
        Cooper->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Cooper);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuSystem = new QMenu(menuBar);
        menuSystem->setObjectName(QString::fromUtf8("menuSystem"));
        menuMember = new QMenu(menuBar);
        menuMember->setObjectName(QString::fromUtf8("menuMember"));
        menuCommittee = new QMenu(menuBar);
        menuCommittee->setObjectName(QString::fromUtf8("menuCommittee"));
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
        menuBar->addAction(menuMember->menuAction());
        menuBar->addAction(menuCommittee->menuAction());
        menuBar->addAction(menuTask->menuAction());
        menuBar->addAction(menuEvent->menuAction());
        menuBar->addAction(menuPrint->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuSystem->addAction(actionLogoff);
        menuSystem->addAction(actionQuit);
        menuMember->addAction(actionAdd_Member);
        menuMember->addAction(actionEdit_Member);
        menuMember->addAction(actionDelete_Member);
        menuCommittee->addAction(actionAdd_Committee);
        menuCommittee->addAction(actionDelete_Committee);
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

        retranslateUi(Cooper);

        QMetaObject::connectSlotsByName(Cooper);
    } // setupUi

    void retranslateUi(QMainWindow *Cooper)
    {
        Cooper->setWindowTitle(QApplication::translate("Cooper", "Cooper", 0, QApplication::UnicodeUTF8));
        actionLogoff->setText(QApplication::translate("Cooper", "Logoff", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("Cooper", "Quit", 0, QApplication::UnicodeUTF8));
        actionAdd_Member->setText(QApplication::translate("Cooper", "Add Member", 0, QApplication::UnicodeUTF8));
        actionEdit_Member->setText(QApplication::translate("Cooper", "Edit Member", 0, QApplication::UnicodeUTF8));
        actionDelete_Member->setText(QApplication::translate("Cooper", "Delete Member", 0, QApplication::UnicodeUTF8));
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
        menuSystem->setTitle(QApplication::translate("Cooper", "System", 0, QApplication::UnicodeUTF8));
        menuMember->setTitle(QApplication::translate("Cooper", "Member", 0, QApplication::UnicodeUTF8));
        menuCommittee->setTitle(QApplication::translate("Cooper", "Committee", 0, QApplication::UnicodeUTF8));
        menuTask->setTitle(QApplication::translate("Cooper", "Task", 0, QApplication::UnicodeUTF8));
        menuEvent->setTitle(QApplication::translate("Cooper", "Event", 0, QApplication::UnicodeUTF8));
        menuPrint->setTitle(QApplication::translate("Cooper", "Print", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("Cooper", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Cooper: public Ui_Cooper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COOPER_H
