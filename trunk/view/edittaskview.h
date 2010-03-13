#ifndef EDITTASKVIEW_H
#define EDITTASKVIEW_H

#include <ctime>

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QMessageBox>

#include "lib/gui/modellistwidget.h"
#include "lib/gui/formlayoutptr.h"

#include "model/taskmodel.h"
#include "model/committeemodel.h"

#include "view/homeview.h"

class EditTaskView : public QDialog
{
    Q_OBJECT
public:
    EditTaskView(TaskModel *selectedtask, QWidget *parent=0);
    ~EditTaskView(void);

private:
    QLineEdit *name;
    QTextEdit *description;
    QRadioButton *pending_status;
    QDateEdit *deadline;
    TaskModel *task;

    void dataInit(void);

public slots:
    void saveChange(void);
    void okTask(void);
    void cancelTask(void);
};

#endif // EDITTASKVIEW_H
