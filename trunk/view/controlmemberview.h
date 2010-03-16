/*
 * membercontrolview.h
 *
 *  Created on: Mar 11, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef MEMBERCONTROLVIEW_H_
#define MEMBERCONTROLVIEW_H_

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "lib/gui/modellistwidget.h"

#include "model/usermodel.h"
#include "model/membermodel.h"
#include "model/permissionmodel.h"

#include "view/addmemberview.h"
#include "view/editmemberview.h"
#include "view/triggermoveoutview.h"
#include "view/triggerinternalmoveview.h"
#include "view/dependantlistview.h"
#include "controller/printcontroller.h"
#include "model/documentmodel.h"

class ControlMemberView : public QWidget {
    Q_OBJECT

public:
    ControlMemberView(QWidget *parent = 0);

private:
    ModelListWidget<MemberModel> *member_list;
    QPushButton *mark_button;
    QPushButton *unmark_button;
    QPushButton *del_button;
    QPushButton *edit_button;
    QPushButton *dependant_button;
    QPushButton *move_out_button;
    QPushButton *internal_move_button;
    QPushButton *print_public_button;
    QPushButton *print_private_button;
    void populateMembers();

public slots:
    void addMember();
    void editMember();
    void deleteMember();
    void markMember();
    void unmarkMember();
    void triggerMoveOut();
    void triggerInternalMove();
    void manageDependants();
    void printPublic();
    void printPrivate();

    /**
     * Change the buttons depending on whether or not members have a
     * certain status.
     */
    void activateButtons();
};

#endif /* MEMBERCONTROLVIEW_H_ */
