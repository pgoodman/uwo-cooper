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
    bday_21->setCalendarPopup(true);

    connect(remove, SIGNAL(clicked()), this, SLOT(removeDependant()));
    connect(save_button, SIGNAL(clicked()), this, SLOT(updateDependant()));
}

/**
 * Remove this dependant.
 */
void DependantListItemView::removeDependant(void) {
    dependant->remove();

    QMessageBox::information(
        this, "Removed Dependant",
        "Removed depedant."
    );

    emit dependantRemoved(this);
}

/**
 * Update this dependant in the db.
 */
void DependantListItemView::updateDependant(void) {
    if(name->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter the dependant's full name."
        );
        return;
    }

    // TODO: check that they are under 21

    dependant->setName(name->text());
    dependant->setBirthday(bday_21->dateTime());
    dependant->save();

    QMessageBox::information(
        this, "Updated Dependant",
        "Updated depedant."
    );
}
