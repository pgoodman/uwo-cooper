/*
 * triggerinternalmoveview.cc
 *
 *  Created on: Mar 14, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "triggerinternalmoveview.h"

TriggerInternalMoveView::TriggerInternalMoveView(MemberModel *chosenMember,
                                                 QWidget *parent)
 : QDialog(parent) {
    FormLayoutPtr layout(this);

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

void TriggerInternalMoveView::okEvent(void) {

    QDateTime moveInDate = move_in_date->dateTime();
    UnitModel *intoUnit = newunit->getModel();

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
        QDateTime in_30_days(moveInDate);
        in_30_days = in_30_days.addDays(30);
        ic->addTask(QString("Move-In Inspection"), *description, in_30_days);

        //
    }

    else if (withMembers->isChecked()) {

    }

    done(QDialog::Accepted);
}

void TriggerInternalMoveView::cancelEvent(void){
    done(QDialog::Rejected);
}
