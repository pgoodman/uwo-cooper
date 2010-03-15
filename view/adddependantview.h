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

#include "lib/gui/formlayoutptr.h"

#include "model/dependantmodel.h"

/**
 * View for items in the dependant list.
 */
class AddDependantView : public QWidget {
    Q_OBJECT
protected:
    QLineEdit *name;
    QDateEdit *bday_21;
    QPushButton *save_button;
    FormLayoutPtr layout;

public:
    AddDependantView(QWidget *parent = 0);

signals:
    void dependantAdded(DependantModel *);
};

#endif /* ADDDEPENDANTVIEW_H_ */
