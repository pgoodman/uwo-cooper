/*
 * modellistitem.h
 *
 *  Created on: Mar 5, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef MODELLISTITEM_H_
#define MODELLISTITEM_H_

#include <iostream>

#include <QString>
#include <QListWidget>
#include <QListWidgetItem>

template <typename T>
class ModelListWidgetItem : public QListWidgetItem {
public:
    ModelListWidgetItem(T *m) : QListWidgetItem(m->toString()), model(m) { }

    T *getModel(void) {
        return model;
    }
private:
    T *model;
};

#endif /* MODELLISTITEM_H_ */
