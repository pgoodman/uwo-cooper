#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H

#include <Qt>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QFormLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QtGui>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCloseEvent>


#include "lib/database.h"
#include "lib/gui/modellistwidget.h"
#include "lib/gui/modellistwidgetitem.h"
#include "lib/gui/formlayoutptr.h"

#include "model/committeemodel.h"
#include "model/taskmodel.h"

#include "view/addtaskview.h"

class TaskListView : public QDialog {
    Q_OBJECT

public:
    TaskListView(CommitteeModel *comm, QWidget *parent=0);
    ~TaskListView(void);

private:
    ModelListWidget<TaskModel> *task_list;
    QPushButton *add_button;
    QPushButton *edit_button;
    QPushButton *delete_button;
    CommitteeModel *committee;

    void populateTaskList(void);

public slots:
    void addTasks();
    void editTasks();
    void deleteTasks();

};

#endif // TASKLISTVIEW_H
