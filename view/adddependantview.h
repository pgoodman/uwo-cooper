/*
 * adddependantview.h
 *
 *  Created on: Mar 15, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef ADDDEPENDANTVIEW_H_
#define ADDDEPENDANTVIEW_H_

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QGridLayout>
#include <QMessageBox>

#include "lib/gui/formlayoutptr.h"

#include "model/membermodel.h"
#include "model/dependantmodel.h"

/**
 * View for items in the dependant list.
 */
class AddDependantView : public QWidget {
    Q_OBJECT
protected:
    MemberModel *member;
    QLineEdit *name;
    QDateEdit *bday_21;

public:
    AddDependantView(MemberModel *m, QWidget *parent = 0);

public slots:
    void addDependant();

signals:
    void dependantAdded(DependantModel *);
};

#endif /* ADDDEPENDANTVIEW_H_ */
