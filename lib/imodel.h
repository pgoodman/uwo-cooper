/*
 * model.h
 *
 *  Created on: Mar 8, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef MODEL_H_
#define MODEL_H_

#define MODEL_CLASS(model_name) friend class IModelBase<model_name>

#include <map>
#include <sstream>
#include <utility>

#include "lib/imodeliterator.h"
#include "lib/database.h"

/**
 * Tags for how to select. These tags specialize how the model should go
 * about finding data.
 */
class select_from_table_tag { };
class select_from_view_tag { };

/**
 * Abstract template class for models. This template imposes the following
 * requirements on any class T being instantiated with it:
 *
 *    T::column_names stirng literal array must exist
 *    T::table_name must exist
 *    T::load(QSqlQuery &q, const int model_id) must exist.
 *
 * Any class T extend IModel<T,S> must call the MODEL_CLASS macro somewhere in
 * the class body.
 *
 * If the model is using the select_from_view_tag then the model must also have
 * the following defined:
 *
 *    T::view_name
 */
template <typename T>
class IModelBase {
public:

    typedef IModelIterator<T> iterator;
    typedef std::pair<iterator, iterator> iterator_range;

    virtual bool save(void) = 0;
    virtual bool remove(void);

    virtual ~IModelBase();

    const int id; // primary key

    static bool removeAll(void);
    static bool removeAll(const char *cond);

protected:
    IModelBase(const int model_id);

    static T *load(const char *table_name, const int model_id);
    static void remember(const int id, T *val);
    static T *recall(const int id);
    static bool isRemembered(const int id);

private:
    static std::map<int, T *> elms;
};

#define IMODEL_CLASS public: \
    IModel(const int); \
    static typename IModelBase<T>::iterator_range findAll(void); \
    static typename IModelBase<T>::iterator_range findAll(const char *cond); \
    static T *findById(const int id); \

/**
 * Base for IModel abstract class.
 */
template <typename T, typename S=select_from_view_tag>
class IModel : public IModelBase<T> {
    IMODEL_CLASS
};

/**
 * Partial Specialization that select from a given view.
 */
template <typename T>
class IModel<T, select_from_view_tag> : public IModelBase<T> {
    IMODEL_CLASS
};

#undef IMODEL_CLASS

// initialize the map
template <typename T>
std::map<int, T *> IModelBase<T>::elms;

/**
 * Constructor, initialize the primary key value.
 */
template <typename T>
IModelBase<T>::IModelBase(const int model_id) : id(model_id) { }

template <typename T, typename S>
IModel<T,S>::IModel(const int model_id) : IModelBase<T>(model_id) { }

template <typename T>
IModel<T,select_from_view_tag>::IModel(const int model_id)
 : IModelBase<T>(model_id) { }

/**
 * Destructor.
 */
template <typename T>
IModelBase<T>::~IModelBase() { }

/**
 * Delete everything from the table of this model.
 */
template <typename T>
bool IModelBase<T>::removeAll(void) {
    return Database::remove(T::table_name, "1=1");
}

template <typename T>
bool IModelBase<T>::removeAll(const char *cond) {
    return Database::remove(T::table_name, cond);
}

/**
 * Remember a loaded model.
 */
template <typename T>
void IModelBase<T>::remember(const int model_id, T *val) {
    if(!isRemembered(model_id)) {
        elms[model_id] = val;
    }
}

/**
 * Recall a previously loaded model. Returns NULL if no model has been
 * loaded yet.
 */
template <typename T>
T *IModelBase<T>::recall(const int model_id) {
    if(!isRemembered(model_id)) {
        return 0;
    }
    return elms[model_id];
}

/**
 * Check whether we have remembered a fetched model.
 */
template <typename T>
bool IModelBase<T>::isRemembered(const int model_id) {
    return elms.end() != elms.find(model_id);
}

/**
 * Return an iterator range of all models in the db for a table.
 */
template <typename T, typename S>
typename IModelBase<T>::iterator_range
IModel<T,S>::findAll(void) {
    return Database::selectAll<T>(T::table_name, "1=1");
}
template <typename T, typename S>
typename IModelBase<T>::iterator_range
IModel<T,S>::findAll(const char *cond) {
    return Database::selectAll<T>(T::table_name, cond);
}

template <typename T>
typename IModelBase<T>::iterator_range
IModel<T,select_from_view_tag>::findAll(void) {
    return Database::selectAll<T>(T::view_name, "1=1");
}
template <typename T>
typename IModelBase<T>::iterator_range
IModel<T,select_from_view_tag>::findAll(const char *cond) {
    return Database::selectAll<T>(T::view_name, cond);
}

/**
 * Load by query.
 */
template <typename T>
T *IModelBase<T>::load(const char *table_name, const int model_id) {
    if(isRemembered(model_id)) {
        return recall(model_id);
    }
    QSqlQuery q(Database::select(table_name, model_id));
    if(!q.isValid()) {
        return 0;
    }
    T *record(T::load(q, model_id));
    q.finish();
    remember(model_id, record);
    return record;
}

/**
 * Load a model by primary key value.
 */
template <typename T, typename S>
T *IModel<T,S>::findById(const int model_id) {
    return IModelBase<T>::load(T::table_name, model_id);
}

template <typename T>
T *IModel<T,select_from_view_tag>::findById(const int model_id) {
    return IModelBase<T>::load(T::view_name, model_id);
}

/**
 * Remove an acrive model from the database.
 */
template <typename T>
bool IModelBase<T>::remove(void) {
    elms.erase(id);
    return Database::remove(T::table_name, id);
}

#endif /* MODEL_H_ */
