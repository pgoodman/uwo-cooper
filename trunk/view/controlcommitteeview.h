/*
 * committeecontrolview.h
 *
 *  Created on: Mar 11, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef COMMITTEECONTROLVIEW_H_
#define COMMITTEECONTROLVIEW_H_

#include <iostream>

#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "lib/gui/modellistwidget.h"

#include "model/usermodel.h"
#include "model/committeemodel.h"
#include "model/permissionmodel.h"

#include "view/addcommitteeview.h"
#include "view/tasklistview.h"

using namespace std;

class ControlCommitteeView : public QWidget {
    Q_OBJECT

public:
    ControlCommitteeView(QWidget *parent = 0);

private:
    QPushButton *add_button;
    QPushButton *edit_button;
    QPushButton *del_button;
    QPushButton *task_button;
    ModelListWidget<CommitteeModel> *committee_list;
    void populateCommittees();

public slots:

    void editCommittee() {
        cout << "show edit committee form." << endl;
    }
    void addCommittee();

    void deleteCommittee();
    void viewCommittee() {
        cout << "show view committee." << endl;
    }
    void viewTasks();

    /**
     * Change the buttons depending on whether or not members have a
     * certain status.
     */
    void activateButtons();
};

#endif /* COMMITTEECONTROLVIEW_H_ */
