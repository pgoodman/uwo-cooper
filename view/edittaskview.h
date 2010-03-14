#ifndef EDITTASKVIEW_H
#define EDITTASKVIEW_H

#include <QWidget>

#include "model/taskmodel.h"
#include "model/committeemodel.h"

#include "view/addtaskview.h"

class EditTaskView : public AddTaskView {
    Q_OBJECT
public:
    EditTaskView(TaskModel *selectedtask,
                 CommitteeModel *comm,
                 QWidget *parent=0);

private:
    TaskModel *task;
    void dataInit(void);

public slots:
    virtual void save(void);
};

#endif // EDITTASKVIEW_H
