#ifndef PRINTCONTROLLER_H
#define PRINTCONTROLLER_H

#include <QPrinter>
#include <QPrintDialog>

#include "lib/document.h"

class PrintController
{
public:
    PrintController(int type);
    ~PrintController();

    void print();
private:
    int doctype;
    QPrinter *printer;
};

#endif // PRINTCONTROLLER_H
