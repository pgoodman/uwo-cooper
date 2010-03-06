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

#include "datatype/modeliterator.h"
#include "modellistitem.h"

template <typename T>
class ModelList : public QListWidget {
    typedef ModelIterator<T,T> iterator;
    typedef pair<iterator,iterator> iterator_pair;
    typedef iterator_pair (iterator_pair_func)(void);

public:

    /**
     * Constructor.
     */
    ModelList(QWidget *parent=0) : QListWidget(parent) { }

    /**
     * Destructor, free the list items.
     */
    ~ModelList(void) {

    }

    /**
     * Get the currently selected item.
     */
    T *getModel(void) {
        QListWidgetItem *item(currentItem());
        if(0 == item) {
            return 0;
        }
        ModelListItem<T> *row = static_cast<ModelListItem<T> *>(item);
        return row->getModel();
    }

    /**
     * Fill the list.
     */
    void fill(iterator_pair_func *f) {
        iterator_pair its(f());
        return fill(its.first, its.second);
    }
    void fill(pair<iterator,iterator> &its) {
        fill(its.first, its.second);
    }
    void fill(iterator &it, iterator &end) {
        clear();
        for(int i = 0; it != end; it++) {
            ModelListItem<T> *item(new ModelListItem<T>(*it));
            insertItem(i++, item);
        }
    }
};

#endif /* MODELLIST_H_ */
