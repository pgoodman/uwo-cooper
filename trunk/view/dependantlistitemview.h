/*
 * dependantlistitemview.h
 *
 *  Created on: Mar 14, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef DEPENDANTLISTITEMVIEW_H_
#define DEPENDANTLISTITEMVIEW_H_

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>

#include "lib/gui/formlayoutptr.h"

#include "model/dependantmodel.h"

#include "view/adddependantview.h"

/**
 * View for items in the dependant list.
 */
class DependantListItemView : public AddDependantView {
    Q_OBJECT
private:
    DependantModel *dependant;

public:
    DependantListItemView(DependantModel *child, QWidget *parent = 0);

public slots:
    void removeDependant(void);
    void updateDependant(void);

signals:
    void dependantRemoved(DependantListItemView *);
};

#endif /* DEPENDANTLISTITEMVIEW_H_ */
