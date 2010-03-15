/*
 * dependantlistitemview.cc
 *
 *  Created on: Mar 14, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "dependantlistitemview.h"

DependantListItemView::DependantListItemView(DependantModel *child,
                                             QWidget *parent)
 : QWidget(parent), dependant(child) {
    name = new QLineEdit;

}

/**
 * Remove this dependant.
 */
void DependantListItemView::removeDependant(void) {
    emit dependantRemoved(this);
}

/**
 * Update this dependant in the db.
 */
void DependantListItemView::updateDependant(void) {


}
