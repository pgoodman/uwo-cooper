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
        if(0 == row) {
            return 0;
        }
        return row->getModel();
    }

    /**
     * Activate some widget when items in this list are selected.
     */
    void activateOnSelect(QWidget *w) {
        (void) w;
    }

    /**
     * Fill the list.
     */
    void fill(pair<iterator,iterator> &its) {
        fill(its.first, its.second);
    }
    void fill(iterator &it, iterator &end) {
        clear();
        for(int i = 0; it != end; it++) {
            ModelListItem<T> *item(new ModelListItem<T>(*it));
            insertItem(i++, item);

            // connect the signals
            /*connect(
                item, SIGNAL(itemActivated()),
                this, SLOT(activateWidgets())
            );*/
        }
    }
};

#endif /* MODELLIST_H_ */
