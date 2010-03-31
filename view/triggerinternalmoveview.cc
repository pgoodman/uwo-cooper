/*
 * triggerinternalmoveview.cc
 *
 *  Created on: Mar 14, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "triggerinternalmoveview.h"

/**
  * Constructor
  */

TriggerInternalMoveView::TriggerInternalMoveView(MemberModel *chosenMember,
                                                 QWidget *parent)
 : QDialog(parent) {
    // Set up the form layout
    FormLayoutPtr layout(this);

    // Get the particular member that is moving
    member = chosenMember;

    // Make button group for empty/occupied unit
    QButtonGroup *occupied_unit_group(new QButtonGroup);
    isEmpty = new QRadioButton;
    withMembers = new QRadioButton;
    occupied_unit_group->addButton(isEmpty);
    occupied_unit_group->addButton(withMembers);

    // make the layout of the form
    first_name = layout << "First Name: " |= new QLineEdit;
    last_name = layout << "Last Name: " |= new QLineEdit;
    user_name = layout << "Login Name: " |= new QLineEdit;
    oldunit = layout << "Old Unit: " |= new QLineEdit;
    newunit = layout << "New Unit: " |= new ModelListWidget<UnitModel>;
    move_in_date = layout << "Move In Date: " |= new QDateEdit;
    isEmpty = layout << "Moving Into Empty Unit?" |= new QRadioButton;
    withMembers = layout << "Moving Into Occupied Unit?" |= new QRadioButton;

    // make and add in the buttons
    ok_button = new QPushButton("Ok");
    QPushButton *cancel(new QPushButton("Cancel"));\
    layout << ok_button | cancel;

    // TODO: does internal move report an error with only 1 unit in the system?
    std::stringstream ss;
    unitNo = member->findUnit();
    ss << "id != " << (unitNo->id);
    UnitModel::iterator_range new_units(UnitModel::findAll(ss.str().c_str()));

    // misc
    first_name->setText(member->getFirstName());
    first_name->setEnabled(false);
    last_name->setText(member->getLastName());
    last_name->setEnabled(false);
    user_name->setText(member->getUserName());
    user_name->setEnabled(false);
    oldunit->setText(QVariant(unitNo->id).toString());
    oldunit->setEnabled(false);
    newunit->fill(new_units);
    newunit->selectFirst();
    move_in_date->setCalendarPopup(true);
    isEmpty->setChecked(true);

    setModal(true);
    setWindowTitle("Trigger Internal Move event");

    // signals / slots
    connect(ok_button, SIGNAL(clicked()), this, SLOT(okEvent()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelEvent()));
}

/**
  * Causes the function to trigger an Internal Move Event
  */

void TriggerInternalMoveView::okEvent(void) {

    // Recieve all the given information about move dates and notice dates, as well as the unit being moved into.
    QDateTime moveInDate = move_in_date->dateTime();
    QDateTime moveOutDate = moveInDate;
    QDateTime noticeDate = QDateTime::currentDateTime();
    UnitModel *intoUnit = newunit->getModel();
    UnitModel *outOfUnit = member->findUnit();

    // If the unit being moved into will be empty upon move in,
    // Set up move in inspection tasks according to the specifications
    if (isEmpty->isChecked() == true) {
        QString *description(new QString);
        QTextStream ss(description);
        ss << "Member Name: " << member->getFirstName() << " " << member->getLastName() << "\n";
        if(member->isTelephoneShared()) {
            ss << "Telephone Number: " << member->getTelephoneNum() << "\n";
        }
        ss << "Unit Number: " << QVariant(intoUnit->id).toString() << "\n";
        ss << "Move-in Date: " << moveInDate.toString("MMMM d, yyyy") << "\n";

        // Get the Inspections Committee
        CommitteeModel *ic(CommitteeModel::findById(
            CommitteeModel::INSPECTIONS_COMMITTEE_ID
        ));

        // Send Move-In Inspection Task
        QDateTime MoveIn_in_30_days(moveInDate);
        MoveIn_in_30_days = MoveIn_in_30_days.addDays(30);
        ic->addTask(QString("Move-In Inspection"), *description, MoveIn_in_30_days);

        // SEND MOVE OUT EVENTS FOR OLD UNIT

        QString *descript2(new QString);
        QTextStream ss2(descript2);
        ss2 << "Member Name: " << member->getFirstName() << " " << member->getLastName() << "\n";
        if(member->isTelephoneShared()) {
            ss2 << "Telephone Number: " << member->getTelephoneNum() << "\n";
        }
        ss2 << "Unit Number: " << QVariant(outOfUnit->id).toString() << "\n";
        ss2 << "Move-in Date: " << moveInDate.toString("MMMM d, yyyy") << "\n";

        // Send First Move-Out Inspection Task
        QDateTime MoveOut_in_30_days(noticeDate);
        MoveOut_in_30_days = MoveOut_in_30_days.addDays(30);
        ic->addTask(QString("Move-out Inspection 1"), *description, MoveOut_in_30_days);

        // Send Second Move-Out Inspection Task
        QDateTime one_week_before(moveOutDate);
        one_week_before = one_week_before.addDays(-7);
        ic->addTask(QString("Move-out Inspection 2"), *description, one_week_before);

        // Send Third Move-Out Inspection Task
        QDateTime dayOf(moveOutDate);
        ic->addTask(QString("Move-out Inspection 3"), *description, dayOf);
    }

    // Else if there will be people remaining in the unit when being moved into,
    // FINISH THIS!!
    else if (withMembers->isChecked()) {

    }

    done(QDialog::Accepted);
}

/**
  * When the options are cancelled
  */

void TriggerInternalMoveView::cancelEvent(void){
    done(QDialog::Rejected);
}