/*
 * addmember.h
 *
 *  Created on: Mar 10, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef ADDMEMBER_H_
#define ADDMEMBER_H_

#include <Qt>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QDateTime>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QMessageBox>

#include "lib/gui/modellistwidget.h"
#include "lib/gui/formlayoutptr.h"

#include "model/permissionmodel.h"
#include "model/membermodel.h"
#include "model/committeemodel.h"
#include "model/unitmodel.h"
#include "model/taskmodel.h"

/*
 * At any time, the Co-ordinator can trigger a New Member event, giving the
 * name and phone number of the new member, their current (pre-Co-op) address,
 * the unit they are moving into, their move-in date, their userid and initial
 * password, and whether the new member requests their telephone number to be
 * confidential. The Co-ordinator should also specify whether they will be
 * moving into an empty unit, or moving in with current members that are
 * currently in the unit.
 */
class AddMemberView : public QDialog {
    Q_OBJECT
protected:
    QLineEdit *first_name;
    QLineEdit *last_name;
    QLineEdit *phone_number;
    QLineEdit *address;
    QLineEdit *password;
    QDateEdit *date_moved_in;
    QLineEdit *user_name;
    QRadioButton *share_phone_number;
    QRadioButton *dont_share_phone;
    QRadioButton *assign_committee;
    QRadioButton *dont_assign_committee;
    QPushButton *save_button;

    ModelListWidget<CommitteeModel> *committee;
    ModelListWidget<UnitModel> *unit;

    void buildForm(FormLayoutPtr &layout);
    void finishForm(FormLayoutPtr &layout);
    virtual bool checkForm(void);
    virtual bool checkUserName(QString name);
    virtual bool checkPerm(PermissionModelSet perm);

    AddMemberView(int *, QWidget *parent=0);

public:
    AddMemberView(QWidget *parent=0);

public slots:
    virtual void tryAccept(void);
    virtual void accept(void);
};

#endif /* ADDMEMBER_H_ */
