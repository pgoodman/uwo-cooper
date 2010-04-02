
#include "view/taskupdatelistview.h"

/**
 * Constructor, pop up the list of tasks that might be updatable.
 */
TaskUpdateListView::TaskUpdateListView(QWidget *parent,
                                       QList<MoveInEventModel *> &events,
                                       QString fn,
                                       QString pn)
 : QDialog(parent), full_name(fn), phone_number(pn) {

    FormLayoutPtr layout(this);

    layout [2] << "At least one other member is moving into the same unit\n"
                  "around the same time. Please select whether or not you\n"
                  "want to update one of the below move-in tasks for the\n"
                  "unit.";

    do_nothing = layout << "Update Task:" |= new QRadioButton("None");

    while(!events.isEmpty()) {
        layout << "" | new QRadioButton(events.takeLast()->task_description);
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

    emit reject();
}
