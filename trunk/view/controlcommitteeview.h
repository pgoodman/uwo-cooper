/*
 * committeecontrolview.h
 *
 *  Created on: Mar 11, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef COMMITTEECONTROLVIEW_H_
#define COMMITTEECONTROLVIEW_H_

#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidgetItem>

#include "lib/gui/modellistwidget.h"

#include "model/usermodel.h"
#include "model/committeemodel.h"
#include "model/permissionmodel.h"

#include "view/addcommitteeview.h"
#include "view/tasklistview.h"

class ControlCommitteeView : public QWidget {
    Q_OBJECT

public:
    ControlCommitteeView(QWidget *parent = 0);

private:
    ModelListWidget<CommitteeModel> *committee_list;
    void populateCommittees();

public slots:

    void editCommittee() {
        cout << "show edit committee form." << endl;
    }
    void addCommittee();

    void deleteCommittee() {
        cout << "show delete committee form." << endl;
    }
    void viewCommittee() {
        cout << "show view committee." << endl;
    }
    void viewTasks();

};

#endif /* COMMITTEECONTROLVIEW_H_ */
