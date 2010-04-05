/*
 * activateannualtaskview.cc
 *
 *  Created on: Mar 24, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "activateannualtaskview.h"

/**
 * Constructor, build the add task form.
 */
ActivateAnnualTaskView::ActivateAnnualTaskView(CommitteeModel *comm,
                                               QWidget *parent)
 : QDialog(parent) {

    // Set up the form layout
    FormLayoutPtr layout(this);

    // Set the committee we're working with
    committee = comm;

    // Month Button Group and Layout
    QButtonGroup *month_group(new QButtonGroup);
    Jan = layout <<= new QRadioButton("Jan");  month_group->addButton(Jan);
    Feb = layout <<= new QRadioButton("Feb");  month_group->addButton(Feb);
    Mar = layout <<= new QRadioButton("Mar");  month_group->addButton(Mar);
    Apr = layout <<= new QRadioButton("Apr");  month_group->addButton(Apr);
    May = layout <<= new QRadioButton("May");  month_group->addButton(May);
    Jun = layout <<= new QRadioButton("Jun");  month_group->addButton(Jun);
    Jul = layout <<= new QRadioButton("Jul");  month_group->addButton(Jul);
    Aug = layout <<= new QRadioButton("Aug");  month_group->addButton(Aug);
    Sep = layout <<= new QRadioButton("Sep");  month_group->addButton(Sep);
    Oct = layout <<= new QRadioButton("Oct");  month_group->addButton(Oct);
    Nov = layout <<= new QRadioButton("Nov");  month_group->addButton(Nov);
    Dec = layout <<= new QRadioButton("Dec");  month_group->addButton(Dec);

    // Button Creation and Addition
    save_button = new QPushButton("Ok");
    QPushButton *cancel(new QPushButton("Cancel"));
    layout << save_button | cancel;

    //Set up extra specification
    Jan->setChecked(true);
    setModal(true);
    setWindowTitle("Activate Annual Task Specs");

    // Connect the 2 buttons to their respective functions
    connect(save_button, SIGNAL(clicked()), this, SLOT(save()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}


/**
 * Destructor.
 */
ActivateAnnualTaskView::~ActivateAnnualTaskView(void) {}

/**
 * Attempt to add a task.
 */
void ActivateAnnualTaskView::save(void) {    

    // Get the list of this committee's task specs and the iterator containing them
    TaskSpecModel::iterator_range taskSpecs (committee->findTaskSpecs());
    TaskSpecModel::iterator &it(taskSpecs.first), &end(taskSpecs.second);

    bool isActivated = false;                                   // True when tasks are activated

    if (Jan->isChecked()) {
        // Check for January tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 1) {                                    // If it's January,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }
    else if (Feb->isChecked()) {
        // Check for February Tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 2) {                                    // If it's February,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }
    else if (Mar->isChecked()) {
        // Check for March Tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 3) {                                    // If it's March,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }
    else if (Apr->isChecked()) {
        // Check for April Tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 4) {                                    // If it's April,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }
    else if (May->isChecked()) {
        // Check for May Tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 5) {                                    // If it's May,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }
    else if (Jun->isChecked()) {
        // Check for June Tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 6) {                                    // If it's June,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }
    else if (Jul->isChecked()) {
        // Check for July Tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 7) {                                    // If it's July,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }
    else if (Aug->isChecked()) {
        // Check for August Tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 8) {                                    // If it's August,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }
    else if (Sep->isChecked()) {
        // Check for September Tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 9) {                                    // If it's September,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }
    else if (Oct->isChecked()) {
        // Check for October Tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 10) {                                   // If it's October,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }
    else if (Nov->isChecked()) {
        // Check for November Tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 11) {                                   // If it's November,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }
    else if (Dec->isChecked()) {
        // Check for December Tasks
        for(; it != end; it++) {
            int date = (*it)->getDeadline().date().month();     // Get the deadline month of task
            if (date == 12) {                                   // If it's December,
                ActivateTaskToList(*it);                        // Activate the task on task list
                isActivated = true;                             // We have activated at least one task
            }
        }
    }

    // If we haven't activated any tasks, send a notice about it and return
    if (isActivated == false) {
            QMessageBox::information(
                this, "No Tasks In This Month",
                "There are no tasks in the chosen month"
            );
            return;
    }

    done(QDialog::Accepted);
}

/**
  * Activate the tasks of the chosen month on the normal task list of the committee
  */

void ActivateAnnualTaskView::ActivateTaskToList(TaskSpecModel *task) {
        // Get the annual task spec's attributes
        QString *description(new QString);
        QString *name(new QString);
        QDateTime *deadline(new QDateTime);
        *description = (*task).getDescription();
        *name = (*task).getName();
        *deadline = (*task).getDeadline();

        // Add task to the task list;
        committee->addTask(*name, *description, *deadline);
}
