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
    FormLayoutPtr layout(this);

    QPushButton *save_button(new QPushButton("Update"));
    QPushButton *remove(new QPushButton("Delete"));
    name = layout <<= new QLineEdit;
    bday_21 = layout |= new QDateEdit;

    layout | save_button | remove;

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
