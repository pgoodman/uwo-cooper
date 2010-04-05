/*
 * form.h
 *
 *  Created on: Mar 10, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef FORM_H_
#define FORM_H_

#include <cassert>

#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QString>

#include "lib/maybe.h"

class FormLayoutPtr : public Maybe<QGridLayout> {
private:
    int voffset;
    int hoffset;
    int next_span;

public:
    FormLayoutPtr(QWidget *parent=0);
    ~FormLayoutPtr();

    FormLayoutPtr &operator<<(const char *);
    FormLayoutPtr &operator|(const char *);
    QLabel *operator<<=(const char *);
    QLabel *operator|=(const char *);

    FormLayoutPtr &operator<<(QString);
    FormLayoutPtr &operator|(QString);
    QLabel *operator<<=(QString);
    QLabel *operator|=(QString);

    FormLayoutPtr &operator[](const int);

    void replaceItem(QWidget *, QWidget *);

    /**
     * Add in a widget to a new line and return the widget.
     */
    template <typename T> T *operator<<=(T *widget);
    template <typename T> FormLayoutPtr &operator<<(T *widget);

    /**
     * Add in a widget to the current line in current column.
     */
    template <typename T> T *operator|=(T *widget);
    template <typename T> FormLayoutPtr &operator|(T *widget);
};

/**
 * Add in a widget to a new line and return a pointer to the widget.
 */
template <typename T>
T *FormLayoutPtr::operator<<=(T *widget) {
    ++(voffset);
    ptr->addWidget(widget, voffset, 0, 1, next_span);
    hoffset = 1;
    next_span = 1;
    return widget;
}

/**
 * Add in a widget to a new line and return a reference to the form layout
 * ptr.
 */
template <typename T>
FormLayoutPtr &FormLayoutPtr::operator<<(T *widget) {
    (*this) <<= widget;
    return *this;
}

/**
 * Add in a widget to the current line in current column and return a pointer
 * to the widget added.
 */
template <typename T>
T *FormLayoutPtr::operator|=(T *widget) {
    assert(voffset >= 0);
    ptr->addWidget(widget, voffset, (hoffset)++, 1, next_span);
    next_span = 1;
    return widget;
}

/**
 * Add in a widget to the current line in current column and return a
 * reference to the form layout ptr.
 */
template <typename T>
FormLayoutPtr &FormLayoutPtr::operator|(T *widget) {
    (*this) |= widget;
    return *this;
}

#endif /* FORM_H_ */
