#ifndef PRINTCONTROLLER_H
#define PRINTCONTROLLER_H

#define SORT_BY_LASTNAME    0
#define SORT_BY_UNIT        1

#include <QPrinter>
#include <QPrintDialog>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>

#include "lib/document.h"
#include "model/committeemodel.h"
#include "model/member_committee_models.h"

class PrintController : public QObject
{
Q_OBJECT

public:
    PrintController(int type);
    PrintController(int type, CommitteeModel *committee);
    ~PrintController();

    void print();

private:
    int doctype;
    int sort_method;
    QPrinter *printer;
    CommitteeModel *selcommittee;

public slots:
    void sortingChanged(int sort);
};

#endif // PRINTCONTROLLER_H
