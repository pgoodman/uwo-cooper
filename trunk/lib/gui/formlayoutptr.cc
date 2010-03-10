/*
 * formlayout.cc
 *
 *  Created on: Mar 10, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "lib/gui/formlayoutptr.h"

/**
 * Constructor, initialize the layout.
 */
FormLayoutPtr::FormLayoutPtr(QWidget *parent)
 : Maybe<QGridLayout>(new QGridLayout(parent)),
   voffset(-1), hoffset(0), next_span(1) {

}

/**
 * Destructor, add in any spanning widgets.
 */
FormLayoutPtr::~FormLayoutPtr(void) { }

/**
 * Make and add a label.
 */
static QLabel *add_label(QGridLayout *layout,
                         const char *text,
                         const int voffset,
                         const int hoffset,
                         const int col_span) {
    QLabel *label(new QLabel(text));
    layout->addWidget(label, voffset, hoffset, 1, col_span);
    return label;
}

/**
 * Add a label to the layout.
 */
FormLayoutPtr &FormLayoutPtr::operator<<(const char *label) {
    add_label(ptr, label, ++voffset, 0, next_span);
    hoffset = 1;
    next_span = 1;
    return *this;
}
QLabel *FormLayoutPtr::operator<<=(const char *label) {
    QLabel *l(add_label(ptr, label, ++voffset, 0, next_span));
    hoffset = 1;
    next_span = 1;
    return l;
}

/**
 * Add in and return a label.
 */
QLabel *FormLayoutPtr::operator|=(const char *label) {
    assert(voffset >= 0);
    QLabel *l(add_label(ptr, label, voffset, hoffset++, next_span));
    next_span = 1;
    return l;
}

FormLayoutPtr &FormLayoutPtr::operator|(const char *label) {
    assert(voffset >= 0);
    add_label(ptr, label, voffset, hoffset++, next_span);
    next_span = 1;
    return *this;
}

/**
 * Add a spanning row and return it.
 */
FormLayoutPtr &FormLayoutPtr::operator[](const int span) {
    next_span = span;
    return *this;
}
