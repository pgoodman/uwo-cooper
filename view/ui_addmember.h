/********************************************************************************
** Form generated from reading UI file 'AddMemberlJ2808.ui'
**
** Created: Thu Mar 4 15:09:13 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ADDMEMBERLJ2808_H
#define ADDMEMBERLJ2808_H

#include <time.h>

#include <iostream>
#include <QtGui>
#include <QDialog>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QTextEdit>
#include <QLayout>

#include "datatype/user.h"
#include "datatype/member.h"
#include "datatype/committee.h"
#include "view/modellist.h"

class Ui_AddMember : public QDialog
{
Q_OBJECT
public:
    QGridLayout *layout;
    QLabel *UserIDLabel;
    QLabel *LastNameLabel;
    QLineEdit *UnitEdit;
    ModelList<Committee> *committee_list;
    QLabel *label;
    QLineEdit *GivenNameEdit;
    QRadioButton *ArrearYesButton;
    QLineEdit *LastNameEdit;
    QLabel *CommitteeLabel;
    QRadioButton *PrivateYesButton;
    QLineEdit *UserIDEdit;
    QLabel *InArrearsLabel;
    QLabel *PasswordLabel;
    QLineEdit *ArrearsAmountEdit;
    QPushButton *addNewButton;
    QLabel *GivenNameLabel;
    QLineEdit *NumberEdit;
    QLineEdit *lineEdit;
    QLabel *NumberLabel;
    QLabel *UnitLabel;
    QRadioButton *ArrearsNoButton;
    QLineEdit *PasswordEdit;
    QRadioButton *PrivateNoButton;
    QLabel *PrivateNoLabel;
    QPushButton *cancelButton;
    QRadioButton *CommitteeNoButton;
    QRadioButton *CommitteeYesButton;
    QLabel *label_2;
    QRadioButton *under21NoButton;
    QRadioButton *Under21YesButton;
    QTextEdit *Under21List;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup_3;
    QButtonGroup *buttonGroup;
  //  Q *;

    Ui_AddMember(QWidget *parent = 0);
    void retranslateUi();

public slots:
    void addMember(void);
};



#endif // ADDMEMBERLJ2808_H
