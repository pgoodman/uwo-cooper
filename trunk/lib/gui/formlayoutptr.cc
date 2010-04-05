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
                         QString(text),
                         const int voffset,
                         const int hoffset,
                         const int col_span) {
    QLabel *label(new QLabel(text));
    layout->addWidget(label, voffset, hoffset, 1, col_span);
    return label;
}

/**
 * Add a label to the layout and return the label added.
 */
QLabel *FormLayoutPtr::operator<<=(const char *label) {
    QLabel *l(add_label(ptr, QString(label), ++voffset, 0, next_span));
    hoffset = 1;
    next_span = 1;
    return l;
}
QLabel *FormLayoutPtr::operator<<=(QString label) {
    QLabel *l(add_label(ptr, label, ++voffset, 0, next_span));
    hoffset = 1;
    next_span = 1;
    return l;
}

/**
 * Add a label but return back a reference to the layout frame pointer.
 */
FormLayoutPtr &FormLayoutPtr::operator<<(const char *label) {
    add_label(ptr, QString(label), ++voffset, 0, next_span);
    hoffset = 1;
    next_span = 1;
    return *this;
}
FormLayoutPtr &FormLayoutPtr::operator<<(QString label) {
    add_label(ptr, label, ++voffset, 0, next_span);
    hoffset = 1;
    next_span = 1;
    return *this;
}

/**
 * Add in a QLabel and return a pointer to the label.
 */
QLabel *FormLayoutPtr::operator|=(const char *label) {
    assert(voffset >= 0);
    QLabel *l(add_label(ptr, QString(label), voffset, hoffset++, next_span));
    next_span = 1;
    return l;
}
QLabel *FormLayoutPtr::operator|=(QString label) {
    assert(voffset >= 0);
    QLabel *l(add_label(ptr, label, voffset, hoffset++, next_span));
    next_span = 1;
    return l;
}

/**
 * Add in and return a reference to the form layout ptr.
 */
FormLayoutPtr &FormLayoutPtr::operator|(const char *label) {
    assert(voffset >= 0);
    add_label(ptr, QString(label), voffset, hoffset++, next_span);
    next_span = 1;
    return *this;
}
FormLayoutPtr &FormLayoutPtr::operator|(QString label) {
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

/**
 * Replace a widget that has been laid out with a new widget. This function
 * will not free the old widget.
 */
void FormLayoutPtr::replaceItem(QWidget *find, QWidget *replace) {
    if(0 == find || 0 == replace) {
        return;
    }

    const int index = ptr->indexOf(find);
    if(-1 == index) {
        return;
    }

    int row, column, row_span, col_span;
    ptr->getItemPosition(index, &row, &column, &row_span, &col_span);
    ptr->removeWidget(find);
    ptr->addWidget(replace, row, column, row_span, col_span);
    ptr->update();
}
