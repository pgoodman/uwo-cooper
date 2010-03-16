#include "printcontroller.h"

PrintController::PrintController(int type){
    doctype = type;
    print();
}
PrintController::~PrintController(){
}

void PrintController::print(){
    printer = new QPrinter(QPrinter::PrinterResolution);
    QPrintDialog *printDialog = new QPrintDialog(printer, 0);

     if (printDialog->exec() == QDialog::Accepted) {
         Document *doc = new Document(doctype);
         doc->print(printer);
     }


}
