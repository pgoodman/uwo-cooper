/*
 * maybe.h
 *
 *  Created on: Mar 9, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef MAYBE_H_
#define MAYBE_H_

#include <iostream>

template <typename T> class Maybe;
template <typename T> T *Just(Maybe<T>);

/**
 * A boxed pointer.
 */
template <typename T>
class Maybe {

    friend T *Just<T>(Maybe<T>);

protected:
    T *ptr;
public:
    /**
     * Constructors.
     */
    Maybe(void) : ptr(0) { }
    Maybe(T *ref) : ptr(ref) { }
    Maybe(const Maybe<T> &boxed_ref) : ptr(boxed_ref.ptr) { }

    /**
     * Pointer stuff.
     */
    T &operator *(void) {
        if(0 == ptr) {
            std::cout << "Attempting null pointer de-reference." << std::endl;
        }
        return *ptr;
    }

    T *operator ->(void) {
        if(0 == ptr) {
            std::cout << "Attempting null pointer de-reference." << std::endl;
        }
        return ptr;
    }

    /**
     * Copy constructors.
     */
    Maybe<T> &operator =(const T *ref) {
        ptr = ref;
    }

    Maybe<T> &operator =(const Maybe<T> ref) {
        ptr = ref.ptr;
    }

    /**
     * Cast back to pointer.
     */
    operator T *(void) {
        return ptr;
    }

    /**
     * Comparisons.
     */
    bool operator ==(T *ref) {
        return ptr == ref;
    }
    bool operator ==(Maybe<T> &ref) {
        return ptr == ref.ptr;
    }
    bool operator !=(T *ref) {
        return ptr != ref;
    }
    bool operator !=(Maybe<T> &ref) {
        return ptr != ref.ptr;
    }


};

/**
 * The naming of this function is to mimick the "Maybe" type.
 */
template <typename T>
T *Just(Maybe<T> boxed_ptr) {
    return boxed_ptr.ptr;
}

#endif /* MAYBE_H_ */
