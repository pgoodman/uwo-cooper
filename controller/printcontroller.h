#ifndef PRINTCONTROLLER_H
#define PRINTCONTROLLER_H

#include <QPrinter>

#include "lib/document.h"

class PrintController
{
public:
    PrintController();
    ~PrintController();

    static void print(int doctype);
};

#endif // PRINTCONTROLLER_H
