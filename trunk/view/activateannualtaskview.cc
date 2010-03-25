
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

ActivateAnnualTaskView::ActivateAnnualTaskView(CommitteeModel *comm, QWidget *parent) : QDialog(parent) {
    FormLayoutPtr layout(this);

    committee = comm;

    // Month Button Group and Layout
    QButtonGroup *month_group(new QButtonGroup);
    Jan = new QRadioButton("Jan");
    Feb = new QRadioButton("Feb");
    Mar = new QRadioButton("Mar");
    Apr = new QRadioButton("Apr");
    May = new QRadioButton("May");
    Jun = new QRadioButton("Jun");
    Jul = new QRadioButton("Jul");
    Aug = new QRadioButton("Aug");
    Sep = new QRadioButton("Sep");
    Oct = new QRadioButton("Oct");
    Nov = new QRadioButton("Nov");
    Dec = new QRadioButton("Dec");

    month_group->addButton(Jan);
    month_group->addButton(Feb);
    month_group->addButton(Mar);
    month_group->addButton(Apr);
    month_group->addButton(May);
    month_group->addButton(Jun);
    month_group->addButton(Jul);
    month_group->addButton(Aug);
    month_group->addButton(Sep);
    month_group->addButton(Oct);
    month_group->addButton(Nov);
    month_group->addButton(Dec);

    layout << Jan;
    layout << Feb;
    layout << Mar;
    layout << Apr;
    layout << May;
    layout << Jun;
    layout << Jul;
    layout << Aug;
    layout << Sep;
    layout << Oct;
    layout << Nov;
    layout << Dec;

    // Button Creation and Addition
    save_button = new QPushButton("Ok");
    QPushButton *cancel(new QPushButton("Cancel"));
    layout << save_button | cancel;

    //Set up extra specification
    Jan->setChecked(true);
    setModal(true);
    setWindowTitle("Activate Annual Task Specs");

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
    TaskSpecModel::iterator_range taskSpecs(committee->findTaskSpecs());

    if (Jan->isChecked()) {
        // Check for January tasks
    }
    else if (Feb->isChecked()) {
        // Check for February Tasks
    }
    else if (Mar->isChecked()) {
        // Check for March Tasks
    }
    else if (Apr->isChecked()) {
        // Check for April Tasks
    }
    else if (May->isChecked()) {
        // Check for May Tasks
    }
    else if (Jun->isChecked()) {
        // Check for June Tasks
    }
    else if (Jul->isChecked()) {
        // Check for July Tasks
    }
    else if (Aug->isChecked()) {
        // Check for August Tasks
    }
    else if (Sep->isChecked()) {
        // Check for September Tasks
    }
    else if (Oct->isChecked()) {
        // Check for October Tasks
    }
    else if (Nov->isChecked()) {
        // Check for November Tasks
    }
    else if (Dec->isChecked()) {
        // Check for December Tasks
    }

    done(QDialog::Accepted);
}
