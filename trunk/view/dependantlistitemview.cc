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
 : AddDependantView(parent), dependant(child) {

    QPushButton *remove(new QPushButton("Delete"));
    layout | remove;

    save_button->setText("Update");
    name->setText(dependant->getName());
    bday_21->setDateTime(dependant->getBirthday());
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
