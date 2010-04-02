
#ifndef TASK_UPDATE_LIST_VIEW_H_
#define TASK_UPDATE_LIST_VIEW_H_

#include <QDialog>
#include <QWidget>
#include <QList>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>

#include "lib/gui/formlayoutptr.h"

#include "model/moveineventmodel.h"
#include "model/membermodel.h"
#include "model/taskmodel.h"

class TaskUpdateListView;
class TaskRadioButton : public QRadioButton {
    Q_OBJECT

    TaskUpdateListView *parent;
    const int task_id;
public:
    TaskRadioButton(QString, TaskUpdateListView *, int);
public slots:
    virtual void updateTask(bool);
};

class TaskUpdateListView : public QDialog {
    Q_OBJECT

    MemberModel *member;
    QRadioButton *do_nothing;
    QString full_name;
    QString phone_number;
    int selected_task_id;

    friend class TaskRadioButton;

public:
    TaskUpdateListView(QWidget *parent,
                       QList<MoveInEventModel *> &,
                       QString fn,
                       QString pn);
    ~TaskUpdateListView();

public slots:
    void updateTask(void);
};

#endif // TASK_UPDATE_LIST_VIEW_H_
