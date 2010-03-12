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
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "lib/gui/modellistwidget.h"

#include "model/usermodel.h"
#include "model/membermodel.h"
#include "model/permissionmodel.h"

#include "view/addmemberview.h"

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
    void populateMembers();

public slots:
    void addMember();
    void editMember();
    void deleteMember();
    void markMember();
    void unmarkMember();

    /**
     * Change the buttons depending on whether or not members have a
     * certain status.
     */
    void activateButtons();
};

#endif /* MEMBERCONTROLVIEW_H_ */
