/*
 * addmemberview.cc
 *
 *  Created on: Mar 10, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "addmemberview.h"

/**
 * Constructor, build the add member form.
 */
AddMemberView::AddMemberView(QWidget *parent) : QDialog(parent) {
    FormLayoutPtr layout(this);

    // make the yes/no buttons for the phone number
    QButtonGroup *share_phone_group(new QButtonGroup);
    QRadioButton *dont_share_phone(new QRadioButton("No"));
    share_phone_number = new QRadioButton("Yes");
    share_phone_group->addButton(share_phone_number);
    share_phone_group->addButton(dont_share_phone);

    // make yes/no buttons for assigning a committee
    QButtonGroup *assign_committee_group(new QButtonGroup);
    assign_committee = new QRadioButton("Yes");
    QRadioButton *dont_assign_committee(new QRadioButton("No"));
    assign_committee_group->addButton(assign_committee);
    assign_committee_group->addButton(dont_assign_committee);

    // make the layout of the form
    first_name = layout << "First Name: " |= new QLineEdit;
    last_name = layout << "Last Name: " |= new QLineEdit;
    phone_number = layout << "Telephone Number: " |= new QLineEdit;
    layout << "Share Telephone Number?: " | share_phone_number;
    layout << "" | dont_share_phone;
    address =  layout << "Address: " |= new QLineEdit;
    date_moved_in = layout << "Date Moved In: " |= new QDateEdit;
    layout << "Set Committee?: " | assign_committee;
    layout << "" | dont_assign_committee;
    committee = layout << "Committee: " |= new ModelListWidget<CommitteeModel>;
    user_name = layout << "Login Name: " |= new QLineEdit;
    password = layout << "Password: " |= new QLineEdit;

    // make and add in the buttons
    QPushButton *add(new QPushButton("Add Member"));
    QPushButton *cancel(new QPushButton("Cancel"));
    layout << add | cancel;

    // misc
    assign_committee->setChecked(true);
    share_phone_number->setChecked(true);
    date_moved_in->setCalendarPopup(true);
    committee->fill(&CommitteeModel::findAll);
    committee->selectFirst();
    setModal(true);
    setWindowTitle("Add Member");

    // signals / slots
    connect(
        assign_committee, SIGNAL(toggled(bool)),
        committee, SLOT(setEnabled(bool))
    );

    connect(add, SIGNAL(clicked()), this, SLOT(addMember()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelAdd()));
}

/**
 * Destructor.
 */
AddMemberView::~AddMemberView(void) { }

/**
 * Attempt to add a member.
 */
void AddMemberView::addMember(void) {
    if(!first_name->isModified()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a surname (family name)."
        );
        return;
    }
    done(QDialog::Accepted);
}

/**
 * Close the add member window.
 */
void AddMemberView::cancelAdd(void) {
    done(QDialog::Rejected);
}
