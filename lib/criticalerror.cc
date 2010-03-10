/*
 * criticalerror.cc
 *
 *  Created on: Mar 2, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "lib/criticalerror.h"

CriticalError::CriticalError(const string t, const string m)
 : runtime_error(m), title(t) {

}

CriticalError::~CriticalError() throw() {

}

const char *CriticalError::header(void) {
    return title.c_str();
}
