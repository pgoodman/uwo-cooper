/*
 * adddependantview.cc
 *
 *  Created on: Mar 15, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "adddependantview.h"

/**
 * Create the widget with the add dependant form.
 */
AddDependantView::AddDependantView(MemberModel *mem, QWidget *parent)
 : QWidget(parent), member(mem) {
    FormLayoutPtr layout(this);

    name = layout <<= new QLineEdit;
    bday_21 = layout |= new QDateEdit;
    QPushButton *save_button = layout |= new QPushButton("Add");

    bday_21->setCalendarPopup(true);

    connect(save_button, SIGNAL(clicked()), this, SLOT(addDependant()));
}

/**
 * Add the dependant.
 */
void AddDependantView::addDependant(void) {
    if(name->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter the dependant's full name."
        );
        return;
    }
    DependantModel *dep(member->addDependant(
        name->text(),
        bday_21->dateTime()
    ));
    name->clear();
    emit dependantAdded(dep);
}
