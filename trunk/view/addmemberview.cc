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

    connect(unit, SIGNAL(itemSelectionChanged()), this, SLOT(checkTask()));
    connect(
        date_moved_in, SIGNAL(dateTimeChanged(const QDateTime &)),
        this, SLOT(checkTask(const QDateTime &))
    );
}

AddMemberView::AddMemberView(int *foo, QWidget *parent) : QDialog(parent) {
    (void) foo;
}

/**
 * A unit has been selected.
 */
void AddMemberView::checkTask(void) {
    checkTask(date_moved_in->dateTime());
}

/**
 * The date has been changed.
 */
void AddMemberView::checkTask(const QDateTime &date) {
    UnitModel *unit_model(unit->getSelectedModel());
    if(0 != unit_model) {
        lookForExistingMoveInTask(unit_model, date);
    }
}

/**
 * Go look for an existing task for the move-in-event and ask the user adding
 * the member whether or not they want to update that task.
 */
void AddMemberView::lookForExistingMoveInTask(UnitModel *model,
                                              const QDateTime t) {
    QList<MoveInEventModel *> events(MoveInEventModel::findAll(model->id, t));
    while(!events.isEmpty()) {
        MoveInEventModel *event(events.takeLast());

        std::cout << event->task_description.toStdString() << '\n';
    }
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

    today = QDateTime::currentDateTime();
    today.setTime(QTime());

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

    // make the button group for whether or not the unit will be empty when
    // the person moves in.
    QButtonGroup *unit_empty_group(new QButtonGroup);
    unit_is_empty = new QRadioButton("Yes");
    unit_not_empty = new QRadioButton("No");
    unit_empty_group->addButton(unit_is_empty);
    unit_empty_group->addButton(unit_not_empty);
    unit_is_empty->setChecked(true);

    // make the layout of the form
    first_name = layout << "First Name: " |= new QLineEdit;
    last_name = layout << "Last Name: " |= new QLineEdit;
    phone_number = layout << "Telephone Number: (numbers only)" |= new QLineEdit;
    layout << "Share Telephone Number?: " | share_phone_number;
    layout << "" | dont_share_phone;
    address =  layout << "Address: " |= new QLineEdit;
    date_moved_in = layout << "Date Moved In: " |= new QDateEdit;
    layout << "Set Committee?: " | assign_committee;
    layout << "" | dont_assign_committee;
    committee = layout << "Committee: " |= new ModelListWidget<CommitteeModel>;
    unit = layout << "Unit: " |= new ModelListWidget<UnitModel>;
    layout << "Unit is Empty?: " | unit_is_empty;
    layout << "" | unit_not_empty;
    user_name = layout << "Login Name: " |= new QLineEdit;
    password = layout << "Password: " |= new QLineEdit;

    date_moved_in->setDate(QDate::currentDate());
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
            "Please enter a given name (first name)."
        );
        return false;
    }

    if(last_name->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a surname (last name)."
        );
        return false;
    }

    if(!Validator::isValidPhoneNo(phone_number->text())) {
        QMessageBox::information(
            this, "Invalid Field",
            "Please enter a valid phone number Phone numbers must be 10 "
            "digits long and be all numbers."
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

    if(date_moved_in->dateTime() < today) {
        QMessageBox::information(
            this, "Invalid Field",
            "Please enter a move in date that is not in the past."
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
        assign_committee->isChecked() ? committee->getSelectedModel() : 0,
        unit->getSelectedModel(),
        unit_is_empty->isChecked()
    );

    QDialog::accept();
}

