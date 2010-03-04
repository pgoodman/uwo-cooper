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

    //typedef T *reference;
    //typedef ModelIterator<T, L> iterator;

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
    q->setForwardOnly(true);
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
        delete query;
    } else {
        query->finish();
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
    if(query->nextResult()) {
        setCurrId();
    }
    if(i > size) {
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
    return this != &other || query != other.query || i != other.i;
}

template <typename T, typename L>
bool ModelIterator<T, L>::operator==(const ModelIterator<T, L> &other) {
    return this == &other && query == other.query && i == other.i;
}

/**
 * Set the current record id.
 */
template <typename T, typename L>
void ModelIterator<T, L>::setCurrId(void) {
    QVariant var = query->value(0);
    curr_id = var.toInt();
}

#endif
