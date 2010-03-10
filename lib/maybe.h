/*
 * maybe.h
 *
 *  Created on: Mar 9, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef MAYBE_H_
#define MAYBE_H_

template <typename T> class Maybe;
template <typename T> T *Just(Maybe<T>);

/**
 * Not quite the Maybe monad, but allows one to pinpoint
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
    Maybe(T *ref) : ptr(ref) { }
    Maybe(const Maybe<T> &boxed_ref) : ptr(boxed_ref.ptr) { }

    /**
     * Pointer stuff.
     */
    T &operator *(void) {
        return *ptr;
    }

    T *operator ->(void) {
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
     * Vast back to pointer.
     */
    operator T *(void) {
        return ptr;
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
