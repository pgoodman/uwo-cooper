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

#include <QSqlQuery>
#include <QSqlResult>
#include <QVariant>
#include <QSqlRecord>

using namespace std;

/**
 * Iterator for going over result sets of users.
 */
template <typename T, typename L>
class ModelIterator : public iterator<input_iterator_tag, T> {

public:
    explicit ModelIterator(QSqlQuery *q, const int s, const int off);
    ~ModelIterator();

    T *operator*();
    ModelIterator<T,L> &operator++ ();
    ModelIterator<T,L> operator++ (int);
    bool operator!=(const ModelIterator<T,L> &other);
    bool operator==(const ModelIterator<T,L> &other);

private:

    void setCurrId(void);

    QSqlQuery *query;
    const int size;
    int i;
    int curr_id;
};

/**
 *
 */

/**
 * Constructor.
 */
template <typename T, typename L>
ModelIterator<T, L>::ModelIterator(QSqlQuery *q, const int s, const int off)
 : query(q), size(s), i(off) {
    assert(query->isSelect());
    if(off >= 0 && off < size) {
        setCurrId();
    }
}

/**
 * Destructor.
 */
template <typename T, typename L>
ModelIterator<T, L>::~ModelIterator() {
    if(!query->isActive()) {
        //delete query;
    } else {
        //query->finish();
    }
}

/**
 *
 */
template <typename T, typename L>
T *ModelIterator<T, L>::operator*() {
    return L::load(curr_id);
}

template <typename T, typename L>
ModelIterator<T, L> &ModelIterator<T, L>::operator++ () {
    ++i;
    if(i < size) {
        query->next();
        setCurrId();
    } else {
        i = size + 1;
    }
    return *this;
}

template <typename T, typename L>
ModelIterator<T, L> ModelIterator<T, L>::operator++ (int) {
    ModelIterator<T, L> tmp(*this);
    ++*this;
    return tmp;
}

template <typename T, typename L>
bool ModelIterator<T, L>::operator!=(const ModelIterator<T, L> &other) {
    //D( cout << query << "!=" << other.query << " || " << i << " != " << other.i << endl; )
    return query != other.query || i != other.i;
}

template <typename T, typename L>
bool ModelIterator<T, L>::operator==(const ModelIterator<T, L> &other) {
    return query == other.query && i == other.i;
}

/**
 * Set the current record id.
 */
template <typename T, typename L>
void ModelIterator<T, L>::setCurrId(void) {
    curr_id = query->value(0).toInt();
    //D( cout << "ModelIterator, current id is " << curr_id << endl; )
}

#endif
