/*
 * model.h
 *
 *  Created on: Mar 8, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <map>
#include <sstream>
#include <utility>

#include "lib/imodeliterator.h"
#include "lib/database.h"

/**
 * Abstract template class for models. This template imposes the following
 * requirements on any class T being instantiated with it:
 *
 *    T::table_name must exist
 *    T::load(QSqlQuery &q, const int model_id) must exist.
 *
 * Any class T extend IModel<T> must make IModel<T> its friend.
 */
template <typename T>
class IModel {
public:

    //friend class IModel<T>;

    typedef IModelIterator<T,T> iterator;
    typedef std::pair<iterator, iterator > iterator_range;

    virtual void save(void) = 0;
    virtual void remove(void);

    static iterator_range findAll(void);
    static T *findById(const int id);

    virtual ~IModel();

    const int id; // primary key

protected:
    IModel(const int model_id);

    static void remember(const int id, T *val);
    static T *recall(const int id);
    static bool isRemembered(const int id);

private:
    static std::map<int, T *> elms;
};

// initialize the map
template <typename T>
std::map<int, T *> IModel<T>::elms;

/**
 * Constructor, initialize the primary key value.
 */
template <typename T>
IModel<T>::IModel(const int model_id) : id(model_id) { }

/**
 * Destructor.
 */
template <typename T>
IModel<T>::~IModel() { }

/**
 * Remember a loaded model.
 */
template <typename T>
void IModel<T>::remember(const int model_id, T *val) {
    if(!isRemembered(model_id)) {
        elms[model_id] = val;
    }
}

/**
 * Recall a previously loaded model. Returns NULL if no model has been
 * loaded yet.
 */
template <typename T>
T *IModel<T>::recall(const int model_id) {
    if(!isRemembered(model_id)) {
        return 0;
    }
    return elms[model_id];
}

/**
 * Check whether we have remembered a fetched model.
 */
template <typename T>
bool IModel<T>::isRemembered(const int model_id) {
    return elms.end() != elms.find(model_id);
}

/**
 * Return an iterator range of all models in the db for a table.
 */
template <typename T>
std::pair<IModelIterator<T,T>, IModelIterator<T,T> >
IModel<T>::findAll(void) {
    return Database::selectAll<T>(T::table_name, "1=1");
}

/**
 * Load a model by primary key value.
 */
template <typename T>
T *IModel<T>::findById(const int model_id) {
    if(isRemembered(model_id)) {
        return recall(model_id);
    }
    QSqlQuery q(Database::select(T::table_name, model_id));
    if(!q.isValid()) {
        return 0;
    }
    T *record(T::load(q, model_id));
    q.finish();
    remember(model_id, record);
    return record;
}

/**
 * Remove an acrive model from the database.
 */
template <typename T>
void IModel<T>::remove(void) {
    Database::remove(T::table_name, id);
    elms.erase(id);
}

#endif /* MODEL_H_ */
