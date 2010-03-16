#include "printcontroller.h"

PrintController::PrintController(){
    printer = new QPrinter(QPrinter::PrinterResolution);
}
PrintController::~PrintController(){
    delete printer;
}

void PrintController::print(int doctype){
    Document *doc = new Document(doctype);
    doc->print(printer);

}
