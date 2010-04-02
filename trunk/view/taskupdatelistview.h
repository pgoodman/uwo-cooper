
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

class TaskUpdateListView : public QDialog {
    Q_OBJECT

    MemberModel *member;
    QRadioButton *do_nothing;
    QString full_name;
    QString phone_number;

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
