/*
 * adddependantview.cc
 *
 *  Created on: Mar 15, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "adddependantview.h"

AddDependantView::AddDependantView(QWidget *parent)
 : QWidget(parent) {
    save_button = new QPushButton("Add");
    name = layout <<= new QLineEdit;
    bday_21 = layout |= new QDateEdit;
    layout | save_button;

    bday_21->setCalendarPopup(true);
    setLayout(layout);
}
