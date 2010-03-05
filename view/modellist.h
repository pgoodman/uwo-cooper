/*
 * modellist.h
 *
 *  Created on: Mar 5, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef MODELLIST_H_
#define MODELLIST_H_

#include <utility>

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>

#include "modeliterator.h"
#include "modellistitem.h"

template <typename T>
class ModelList : public QListWidget {
    typedef ModelIterator<T,T> iterator;

public:

    /**
     * Constructor.
     */
    ModelList(QWidget *parent) : QListWidget(parent) { }

    /**
     * Destructor, free the list items.
     */
    ~ModelList(void) {

    }

    /**
     * Get the currently selected item.
     */
    T *currentItem(void) {
        ModelListItem<T> *row = currentItem();
        return row->getModel();
    }

    /**
     * Fill the list.
     */
    void fill(pair<iterator,iterator> &its) {
        fill(its.first, its.second);
    }
    void fill(iterator &it, iterator &end) {
        for(int i = count(); it != end; it++) {
            insertItem(i++, new ModelListItem<T>(*it));
        }
    }
};

#endif /* MODELLIST_H_ */
