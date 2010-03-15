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
    buildForm(layout);
    finishForm(layout);
}
AddMemberView::AddMemberView(int *foo, QWidget *parent) : QDialog(parent) {
    (void) foo;
}

/**
 * Check to see if the active user has a permission set.
 */
bool AddMemberView::checkPerm(PermissionModelSet perm) {
    (void) perm;
    return true;
}

/**
 * Build the form.
 */
void AddMemberView::buildForm(FormLayoutPtr &layout) {
    // make the yes/no buttons for the phone number
    QButtonGroup *share_phone_group(new QButtonGroup);
    dont_share_phone = new QRadioButton("No");
    share_phone_number = new QRadioButton("Yes");
    share_phone_group->addButton(share_phone_number);
    share_phone_group->addButton(dont_share_phone);

    // make yes/no buttons for assigning a committee
    QButtonGroup *assign_committee_group(new QButtonGroup);
    assign_committee = new QRadioButton("Yes");
    dont_assign_committee = new QRadioButton("No");
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
    unit = layout << "Unit: " |= new ModelListWidget<UnitModel>;
    user_name = layout << "Login Name: " |= new QLineEdit;
    password = layout << "Password: " |= new QLineEdit;
}

/**
 * Finish building the form and connect the various parts of it.
 */
void AddMemberView::finishForm(FormLayoutPtr &layout) {
    // make and add in the buttons
    save_button = new QPushButton("Add Member");
    QPushButton *cancel(new QPushButton("Cancel"));
    layout << save_button | cancel;

    // misc
    assign_committee->setChecked(true);
    share_phone_number->setChecked(true);
    date_moved_in->setCalendarPopup(true);
    committee->fill(&CommitteeModel::findAll);
    unit->fill(&UnitModel::findAll);
    committee->selectFirst();
    unit->selectFirst();

    setModal(true);
    setWindowTitle("Add Member");

    // signals / slots
    connect(
        assign_committee, SIGNAL(toggled(bool)),
        committee, SLOT(setEnabled(bool))
    );

    connect(save_button, SIGNAL(clicked()), this, SLOT(tryAccept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

/**
 * Attempt Check the form.
 */
bool AddMemberView::checkForm(void) {

    if(first_name->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a given name (family name / last name)."
        );
        return false;
    }

    if(last_name->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a surname (family name / last name)."
        );
        return false;
    }

    if(phone_number->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a telephone number."
        );
        return false;
    }

    if(address->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter an address for where the person lived before "
            "the co-op."
        );
        return false;
    }

    if(user_name->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter an log in name."
        );
        return false;
    } else if(!checkUserName(user_name->text())) {
        QMessageBox::information(
            this, "Bad Login Name",
            "Please enter an different log in name. The entered "
            "login name is already in use."
        );
        return false;
    }

    if(password->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter an password."
        );
        return false;
    }

    return true;
}

/**
 * Check the user name of the member.
 */
bool AddMemberView::checkUserName(QString name) {
    return !UserModel::nameExists(name);
}

/**
 * Attempt to accept, i.e. attempt to add the user.
 */
void AddMemberView::tryAccept(void) {
    if(this->checkForm()) {
        emit accept();
    }
}

/**
 * Add a member.
 */
void AddMemberView::accept(void) {

    MemberModel::create(
        share_phone_number->isChecked(),
        date_moved_in->dateTime(),
        phone_number->text(),
        user_name->text(),
        first_name->text(),
        last_name->text(),
        address->text(),
        password->text(),
        assign_committee->isChecked() ? committee->getModel() : 0,
        unit->getModel()
    );

    QDialog::accept();
}

