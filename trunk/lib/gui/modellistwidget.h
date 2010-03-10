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

#include "lib/imodeliterator.h"
#include "lib/gui/modellistwidgetitem.h"

template <typename T>
class ModelListWidget : public QListWidget {

    typedef IModelIterator<T,T> iterator;
    typedef std::pair<iterator,iterator> iterator_range;
    typedef iterator_range (iterator_range_func)(void);

public:

    /**
     * Constructor.
     */
    ModelListWidget(QWidget *parent=0);

    /**
     * Destructor, free the list items.
     */
    ~ModelListWidget(void);

    /**
     * Get the currently selected item.
     */
    T *getModel(void);

    /**
     * Select the first item in the list. This forces at least one unit to
     * always be selected.
     */
    void selectFirst(void);

    /**
     * Fill the list.
     */
    void fill(iterator_range_func *f);
    void fill(iterator_range &its);
    void fill(iterator &it, iterator &end);
};

/**
 * For linking purposes the definition must be in here.
 */

template <typename T>
ModelListWidget<T>::ModelListWidget(QWidget *parent) : QListWidget(parent) { }

template <typename T>
ModelListWidget<T>::~ModelListWidget() { }

template <typename T>
T * ModelListWidget<T>::getModel(void) {
    QListWidgetItem *item(currentItem());
    if(0 == item) {
        return 0;
    }
    ModelListWidgetItem<T> *row = static_cast<ModelListWidgetItem<T> *>(item);
    return row->getModel();
}

template <typename T>
void ModelListWidget<T>::selectFirst(void) {
    if(0 < count()) {
        setItemSelected(item(0), true);
    }
}

template <typename T>
void ModelListWidget<T>::fill(iterator_range_func *f) {
    iterator_range its(f());
    return fill(its.first, its.second);
}

template <typename T>
void ModelListWidget<T>::fill(iterator_range &its) {
    fill(its.first, its.second);
}

template <typename T>
void ModelListWidget<T>::fill(iterator &it, iterator &end) {
    clear();
    for(int i = 0; it != end; it++) {
        ModelListWidgetItem<T> *item(new ModelListWidgetItem<T>(*it));
        insertItem(i++, item);
    }
}

#endif /* MODELLIST_H_ */
