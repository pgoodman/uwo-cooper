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
#include <assert.h>
#include <utility>

#include <QSqlQuery>
#include <QSqlResult>
#include <QVariant>
#include <QSqlRecord>

using namespace std;

/**
 * IModelIterator for going over result sets of users.
 */
template <typename T, typename L>
class IModelIterator : public iterator<input_iterator_tag, T> {

public:
    ~IModelIterator();

    T *operator*();
    IModelIterator<T,L> &operator++ ();
    IModelIterator<T,L> operator++ (int);
    bool operator!=(const IModelIterator<T,L> &other);
    bool operator==(const IModelIterator<T,L> &other);

    static pair<IModelIterator<T,L>, IModelIterator<T,L> >
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

    int id;
};

/**
 * For linking purposes the definition must be in here.
 */

/**
 * Constructor.
 */
template <typename T, typename L>
IModelIterator<T, L>::IModelIterator(QSqlQuery q,
                                const int s,
                                const int off,
                                const int query_id)
 : query(q), size(s), i(off), is_used(false), id(query_id) {
    assert(query.isSelect());
    if(off >= 0 && off < size) {
        setCurrId();
    }
    if(0 == off && 0 == size) {
        i = 1;
    }
}

/**
 * Destructor.
 */
template <typename T, typename L>
IModelIterator<T, L>::~IModelIterator() { }

/**
 *
 */
template <typename T, typename L>
T *IModelIterator<T, L>::operator*() {
    return L::findById(curr_id);
}

template <typename T, typename L>
IModelIterator<T, L> &IModelIterator<T, L>::operator++ () {
    ++i;
    if(i < size) {
        query.next();
        setCurrId();
    } else {
        i = size + 1;
    }
    return *this;
}

template <typename T, typename L>
IModelIterator<T, L> IModelIterator<T, L>::operator++ (int) {
    IModelIterator<T, L> tmp(*this);
    ++*this;
    return tmp;
}

template <typename T, typename L>
bool IModelIterator<T, L>::operator!=(const IModelIterator<T, L> &other) {
    //D( cout << id << "!=" << other.id << " || " << i << " != " << other.i << endl; )
    return id != other.id || i != other.i;
}

template <typename T, typename L>
bool IModelIterator<T, L>::operator==(const IModelIterator<T, L> &other) {
    return id == other.id && i == other.i;
}

/**
 * Set the current record id.
 */
template <typename T, typename L>
void IModelIterator<T, L>::setCurrId(void) {
    curr_id = query.value(0).toInt();
    //D( cout << "IModelIterator, current id is " << curr_id << endl; )
}

template <typename T, typename L>
pair<IModelIterator<T,L>, IModelIterator<T,L> >
IModelIterator<T, L>::make(QSqlQuery query, const int size) {
    static int id = 0;
    query.first();
    IModelIterator<T, L> start(query, size, 0, id);
    IModelIterator<T, L> end(query, size, size + 1, id++);
    return make_pair(start, end);
}

#endif
