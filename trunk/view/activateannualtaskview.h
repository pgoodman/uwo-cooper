#ifndef ACTIVATEANNUALTASKVIEW_H
#define ACTIVATEANNUALTASKVIEW_H

#include <QWidget>
#include <QDialog>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QMessageBox>

#include "lib/gui/modellistwidget.h"
#include "lib/gui/formlayoutptr.h"

#include "model/taskmodel.h"
#include "model/committeemodel.h"

class ActivateAnnualTaskView : public QDialog {
    Q_OBJECT

protected:
    QPushButton *save_button;
    QRadioButton *Jan, *Feb, *Mar, *Apr, *May, *Jun, *Jul, *Aug, *Sep, *Oct, *Nov, *Dec;
    CommitteeModel *committee;
    TaskSpecModel *annualTasks;

public:
    ActivateAnnualTaskView(CommitteeModel *comm, QWidget *parent=0);
    ~ActivateAnnualTaskView(void);
    void ActivateTaskToList(TaskSpecModel *task);
    
public slots:
    virtual void save(void);
};


#endif // ACTIVATEANNUALTASKVIEW_H
