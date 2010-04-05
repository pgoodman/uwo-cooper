/*
 * modeliterator.h
 *
 *  Created on: Mar 3, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef MODEL_ITERATOR_H_
#define MODEL_ITERATOR_H_

#include <iterator>
#include <iostream>
#include <cassert>
#include <utility>

#include <QSqlQuery>
#include <QSqlResult>
#include <QVariant>
#include <QSqlRecord>

using namespace std;

/**
 * IModelIterator for going over result sets of users. This is a STL-
 * compatible iterator
 */
template <typename T>
class IModelIterator : public iterator<input_iterator_tag, T> {

public:
    ~IModelIterator();

    T *operator*();
    IModelIterator<T> &operator++ ();
    IModelIterator<T> operator++ (int);
    bool operator!=(const IModelIterator<T> &other);
    bool operator==(const IModelIterator<T> &other);

    static pair<IModelIterator<T>, IModelIterator<T> >
    make(QSqlQuery q, const int size);

private:
    explicit IModelIterator(QSqlQuery q,
                            const int size,
                            const int off,
                            const int query_id);

    void setCurrId(void);

    QSqlQuery query;
    const int size;
    int i;
    int curr_id;
    bool is_used;

    const int id;
};

/**
 * For linking purposes the definition must be in here.
 */

/**
 * Constructor.
 */
template <typename T>
IModelIterator<T>::IModelIterator(QSqlQuery q,
                                const int s,
                                const int off,
                                const int query_id)
 : size(s), i(off), is_used(false), id(query_id) {
    if(0 == off && 0 == size) {
        i = 1;
    } else if(off >= 0 && off < size) {
        assert(q.isSelect());
        query = q;
        setCurrId();
    }
}

/**
 * Destructor.
 */
template <typename T>
IModelIterator<T>::~IModelIterator() { }

/**
 * Return a pointer to the current item pointed to in the iterator.
 */
template <typename T>
T *IModelIterator<T>::operator*() {
    return T::findById(curr_id);
}

/**
 * Advance the iterator.
 */
template <typename T>
IModelIterator<T> &IModelIterator<T>::operator++ () {
    ++i;
    if(i < size) {
        query.next();
        setCurrId();
    } else {
        i = size + 1;
    }
    return *this;
}
template <typename T>
IModelIterator<T> IModelIterator<T>::operator++ (int) {
    IModelIterator<T> tmp(*this);
    ++(*this);
    return tmp;
}

/**
 * Compare two iterators.
 */
template <typename T>
bool IModelIterator<T>::operator!=(const IModelIterator<T> &other) {
    return id != other.id || i != other.i;
}

/**
 * Compare two iterators.
 */
template <typename T>
bool IModelIterator<T>::operator==(const IModelIterator<T> &other) {
    return id == other.id && i == other.i;
}

/**
 * Set the current record id.
 */
template <typename T>
void IModelIterator<T>::setCurrId(void) {
    curr_id = query.value(0).toInt();
}

/**
 * Return a pair of (begin, end) iterators.
 */
template <typename T>
pair<IModelIterator<T>, IModelIterator<T> >
IModelIterator<T>::make(QSqlQuery query, const int size) {
    static int id = 0;
    query.first();
    IModelIterator<T> start(query, size, 0, id);
    IModelIterator<T> end(query, size, size + 1, id++);
    return make_pair(start, end);
}

#endif
