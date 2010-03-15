/*
 * dependantlistview.h
 *
 *  Created on: Mar 14, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef DEPENDANTLISTVIEW_H_
#define DEPENDANTLISTVIEW_H_

#include <QWidget>

#include "model/membermodel.h"
#include "model/dependantmodel.h"

#include "view/dependantlistitemview.h"

class DependantListView : public QWidget {
    Q_OBJECT

public:
    DependantListView(MemberModel *member, QWidget *parent = 0);

private:

    MemberModel *member;

public slots:
    void removeDependantFromList(DependantListItemView *);
};

#endif /* DEPENDANTLISTVIEW_H_ */
