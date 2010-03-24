#ifndef ADDANNUALTASKVIEW_H
#define ADDANNUALTASKVIEW_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QMessageBox>

#include "lib/gui/modellistwidget.h"
#include "lib/gui/formlayoutptr.h"

#include "model/taskmodel.h"
#include "model/committeemodel.h"

class AddAnnualTaskView : public QDialog {
    Q_OBJECT

protected:
    QPushButton *save_button;
    QLineEdit *name;
    QTextEdit *description;
    QDateEdit *deadline;
    CommitteeModel *committee;

public:
    AddAnnualTaskView(CommitteeModel *comm, QWidget *parent=0);
    ~AddAnnualTaskView(void);

public slots:
    virtual void save(void);
};
#endif // ADDANNUALTASKVIEW_H
