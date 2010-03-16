#ifndef PRINTCONTROLLER_H
#define PRINTCONTROLLER_H

#include <QPrinter>

#include "lib/document.h"

class PrintController
{
public:
    PrintController();
    ~PrintController();

    void print(int doctype);
private:
    QPrinter *printer;
};

#endif // PRINTCONTROLLER_H
