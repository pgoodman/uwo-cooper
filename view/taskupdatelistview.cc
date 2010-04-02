
#include "view/taskupdatelistview.h"

/**
 * Constructor, pop up the list of tasks that might be updatable.
 */
TaskUpdateListView::TaskUpdateListView(QWidget *parent,
                                       QList<MoveInEventModel *> &events,
                                       QString fn,
                                       QString pn)
 : QDialog(parent), full_name(fn), phone_number(pn), selected_task_id(0) {

    FormLayoutPtr layout(this);

    layout [2] << "At least one other member is moving into the same unit\n"
                  "around the same time. Please select whether or not you\n"
                  "want to update one of the below move-in tasks for the\n"
                  "unit.";

    do_nothing = layout << "Update Task:" |= new QRadioButton("None");

    while(!events.isEmpty()) {
        MoveInEventModel *event(events.takeLast());
        layout << "" | new TaskRadioButton(
            event->task_description,
            this,
            event->task_id
        );
    }

    QPushButton *cont(layout [2] <<= new QPushButton("Continue"));
    connect(cont, SIGNAL(clicked()), this, SLOT(updateTask()));

    do_nothing->setChecked(true);
}

TaskUpdateListView::~TaskUpdateListView(void) { }

void TaskUpdateListView::updateTask(void) {

    if(do_nothing->isChecked()) {
        emit accept();
        return;
    }

    if(0 != selected_task_id) {
        TaskModel *task(TaskModel::findById(selected_task_id));
        QString new_desc("Member Name: ");
        new_desc += full_name;
        new_desc += "\n";

        if(!phone_number.isEmpty()) {
            new_desc += "Phone Number: ";
            new_desc += phone_number;
            new_desc += "\n";
        }

        new_desc += task->getDescription();

        task->setDescription(new_desc);
        task->save();
    }

    emit reject();
}

TaskRadioButton::TaskRadioButton(QString s, TaskUpdateListView *v, int id)
 : QRadioButton(s), parent(v), task_id(id) {
    connect(this, SIGNAL(toggled(bool)), this, SLOT(updateTask(bool)));
}

void TaskRadioButton::updateTask(bool on) {
    if(on) {
        parent->selected_task_id = task_id;
    }
}

