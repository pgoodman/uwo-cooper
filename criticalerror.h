/*
 * criticalerror.h
 *
 *  Created on: Mar 2, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef CRITICALERROR_H_
#define CRITICALERROR_H_

#include <stdexcept>
#include <string>

using namespace std;

/**
 * Exception class for errors that result in the app not being able to function
 * past the point of the error. The title is included so that a
 * QMessageBox::critical can be used.
 */
class CriticalError : public runtime_error {
public:
    explicit CriticalError(const string title, const string message);
    virtual ~CriticalError() throw();

    const char *header(void);
private:
    const string title;
};

#endif /* CRITICALERROR_H_ */
