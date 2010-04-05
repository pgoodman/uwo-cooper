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
#include <QAbstractItemView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>

#include "lib/imodeliterator.h"
#include "lib/gui/modellistwidgetitem.h"

/**
 * List item widget that takes in an iterator range of model pointers and
 * then allows the user to select one (or many) of the widgets. The rows of
 * the list item are the IModel::toString() of the model.
 */
template <typename T>
class ModelListWidget : public QListWidget {

    typedef IModelIterator<T> iterator;
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
    T *getSelectedModel(void);
    QList<T *> getSelectedModels(void);

    /**
     * Get all the models.
     */
    QList<T *> getModels(void);

    /**
     * Select a specific model.
     */
    void selectModel(T *model);

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

    /**
     * Add a model to the list.
     */
    void addModel(T *model);

    /**
     * Remove one of the models from the list.
     */
    void removeModel(T *model);

    /**
     * Toggle allowing multiple selection.
     */
    void setMultipleSelect(const bool yes);
};

/**
 * For linking purposes the definitions must be in here.
 */

/**
 * Constructor.
 */
template <typename T>
ModelListWidget<T>::ModelListWidget(QWidget *parent) : QListWidget(parent) { }

template <typename T>
ModelListWidget<T>::~ModelListWidget() { }

/**
 * Select one of the models in the widget.
 */
template <typename T>
void ModelListWidget<T>::selectModel(T *model) {

    if(0 == model) {
        return;
    }

    QListWidgetItem *row(0);
    ModelListWidgetItem<T> *model_row(0);
    for(int i = 0; i < count(); ++i) {
        row = item(i);
        if(0 == row) {
            continue;
        }
        model_row = static_cast<ModelListWidgetItem<T> *>(row);
        if(model == model_row->getModel()) {
            setItemSelected(row, true);
            break;
        }
    }
}

/**
 * Return one of the selected rows as a model, if any.
 */
template <typename T>
T * ModelListWidget<T>::getSelectedModel(void) {
    QList<QListWidgetItem *> items(selectedItems());
    if(0 == items.count()) {
        return 0;
    }
    QListWidgetItem *item(items.front());
    if(0 == item) {
        return 0;
    }
    ModelListWidgetItem<T> *row = static_cast<ModelListWidgetItem<T> *>(item);
    return row->getModel();
}

/**
 * Return a QList of model pointers referring to the rows selected in the
 * list widget.
 */
template <typename T>
QList<T *> ModelListWidget<T>::getSelectedModels(void) {
    QList<T *> list;
    ModelListWidgetItem<T> *row;
    QListWidgetItem *item;
    QList<QListWidgetItem *> items(selectedItems());

    while(!items.isEmpty()) {
        item = items.takeLast();
        row = static_cast<ModelListWidgetItem<T> *>(item);
        list.append(row->getModel());
    }

    return list;
}

/**
 * Return all model pointers that are listed in the widget.
 */
template <typename T>
QList<T *> ModelListWidget<T>::getModels(void) {
    QList<T *> list;
    for(int i = 0; i < count(); ++i) {
        list.append(
            static_cast<ModelListWidgetItem<T> *>(item(i))->getModel()
        );
    }

    return list;
}

/**
 * Select the first item in the widget. This is a convenience function for
 * when we want to guarantee that /something/ is selected.
 */
template <typename T>
void ModelListWidget<T>::selectFirst(void) {
    if(0 < count()) {
        setItemSelected(item(0), true);
    }
}

/**
 * Fill the widget with models.
 */
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

/**
 * Add a single model to the list widget.
 */
template <typename T>
void ModelListWidget<T>::addModel(T *model) {
    insertItem(count(), new ModelListWidgetItem<T>(model));
}

/**
 * Remove a model from the widget.
 */
template <typename T>
void ModelListWidget<T>::removeModel(T *model) {
    ModelListWidgetItem<T> *item_widget;
    for(int i = 0; i < count(); ++i) {
        item_widget = static_cast<ModelListWidgetItem<T> *>(item(i));
        if(item_widget->getModel() == model) {
            takeItem(i);
        }
    }
}

/**
 * Enable/disable multiple selection of the items in the widget.
 */
template <typename T>
void ModelListWidget<T>::setMultipleSelect(const bool set_it) {
    setSelectionMode(set_it ?
        QAbstractItemView::MultiSelection : QAbstractItemView::SingleSelection
    );
}

#endif /* MODELLIST_H_ */
