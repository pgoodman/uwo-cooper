/*
 * dependantlistview.cc
 *
 *  Created on: Mar 14, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "view/dependantlistview.h"

/**
 * Constructor, make the list.
 */
DependantListView::DependantListView(MemberModel *user, QWidget *parent)
 : QWidget(parent), member(user) {

}
/**
 * Remove a dependant list item view from the list.
 */
void DependantListView::removeDependantFromList(DependantListItemView *dep) {
    (void) dep;
}
