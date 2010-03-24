#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H

#include <QDialog>
#include <QPushButton>
#include <QWidget>

#include "lib/database.h"
#include "lib/gui/modellistwidget.h"
#include "lib/gui/formlayoutptr.h"

#include "model/committeemodel.h"
#include "model/taskmodel.h"
#include "model/usermodel.h"

#include "view/edittaskview.h"
#include "view/addtaskview.h"
#include "view/addannualtaskview.h"

class TaskListView : public QDialog {
    Q_OBJECT

public:
    TaskListView(CommitteeModel *comm, QWidget *parent=0);
    ~TaskListView(void);

private:
    ModelListWidget<TaskModel> *task_list;
    ModelListWidget<TaskSpecModel> *annualTask_list;
    QPushButton *add_button;
    QPushButton *edit_button;
    QPushButton *delete_button;
    QPushButton *add_annual_button;
    QPushButton *delete_annual_button;
    QPushButton *activate_annual_button;
    CommitteeModel *committee;

    void populateTaskList(void);
    void populateAnnualTaskList(void);

public slots:
    void addTasks();
    void addAnnualTasks();
    void deleteAnnualTasks();
    void activateAnnualTasks();
    void editTasks();
    void deleteTasks();
    void activateButtons(void);
    void activateSpecButtons(void);
};

#endif // TASKLISTVIEW_H
