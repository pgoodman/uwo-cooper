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

    layout <<= new QLabel("Dependant Full Name");
    layout |= new QLabel("Dependant Birthday");
    name = layout <<= new QLineEdit;
    bday_21 = layout |= new QDateEdit;
    QPushButton *save_button = layout |= new QPushButton("Add");

    bday_21->setCalendarPopup(true);
    this->setWindowModality(Qt::ApplicationModal);
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

    // TODO: check that they are under 21

    DependantModel *dep(member->addDependant(
        name->text(),
        bday_21->dateTime()
    ));
    name->clear();

    QMessageBox::information(this, "Dependant Added", "Dependant added.");
    emit dependantAdded(dep);
}
