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

TriggerInternalMoveView::TriggerInternalMoveView(UnitModel *chosenUnit,
                                                 QWidget *parent)
 : QDialog(parent) {

    // Set up the form layout
    FormLayoutPtr layout(this);

    // Get the particular member that is moving
    unitNo = chosenUnit;

    // Make button group for empty/occupied unit
    QButtonGroup *occupied_unit_group(new QButtonGroup);
    isEmpty = new QRadioButton;
    withMembers = new QRadioButton;
    occupied_unit_group->addButton(isEmpty);
    occupied_unit_group->addButton(withMembers);

    // make the layout of the form
    newunit = layout << "New Unit: " |= new ModelListWidget<UnitModel>;
    membersMoving = layout << "Choose members who are moving: " |= new ModelListWidget<MemberModel>;
    move_in_date = layout << "Move In Date: " |= new QDateEdit;
    isEmpty = layout << "Moving Into Empty Unit?" |= new QRadioButton;
    withMembers = layout << "Moving Into Occupied Unit?" |= new QRadioButton;

    // make and add in the buttons
    ok_button = new QPushButton("Ok");
    QPushButton *cancel(new QPushButton("Cancel"));\
    layout << ok_button | cancel;

    // TODO: does internal move report an error with only 1 unit in the system?
    std::stringstream ss;
    ss << "id != " << (unitNo->id);
    UnitModel::iterator_range new_units(UnitModel::findAll(ss.str().c_str()));
    newunit->fill(new_units);
    newunit->selectFirst();

    std::stringstream ss2;
    ss2 << "id != " << (unitNo->id);
    MemberModel::iterator_range memberList(MemberModel::findAll(ss2.str().c_str()));
    membersMoving->setMultipleSelect(true);
    membersMoving->fill(memberList);
    membersMoving->selectFirst();

    // misc
    move_in_date->setCalendarPopup(true);
    isEmpty->setChecked(true);

    setModal(true);
    setWindowTitle("Trigger Internal Move event");

    // signals / slots
    connect(ok_button, SIGNAL(clicked()), this, SLOT(okEvent()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelEvent()));
    connect(
        membersMoving, SIGNAL(itemSelectionChanged()),
        this, SLOT(activateEmptyUnit())
    );

}

/**
 * De/activate the check box depending on whether all members are chosen or not
 */
void TriggerInternalMoveView::activateEmptyUnit () {
    QList<MemberModel*> members(membersMoving->getSelectedModels());
    oldUnitEmpty = (membersMoving->count() == members.count());
}

/**
  * Causes the function to trigger an Internal Move Event
  */

void TriggerInternalMoveView::okEvent(void) {

    // Recieve all the given information about move dates and notice dates, as well as the unit being moved into.
    QDateTime moveInDate = move_in_date->dateTime();
    QDateTime moveOutDate = moveInDate;
    QDateTime noticeDate = QDateTime::currentDateTime();
    UnitModel *intoUnit = newunit->getSelectedModel();
    UnitModel *outOfUnit = unitNo;
    memberList1 = membersMoving->getSelectedModels();
    memberList2 = memberList1;

    // If the unit being moved into will be empty upon move in,
    // Set up move in inspection tasks according to the specifications
    if (isEmpty->isChecked() == true) {
        QString *description(new QString);
        QTextStream ss(description);

        while (!(memberList1.isEmpty())) {
            MemberModel *temp = memberList1.first();
            ss << "Member Name: " << temp->getFirstName() << " " << temp->getLastName() << "\n";
            if(temp->isTelephoneShared()) {
                ss << "Telephone Number: " << temp->getTelephoneNum() << "\n";
            }
            memberList1.removeFirst();
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
    }

    if (oldUnitEmpty == true) {
        // SEND MOVE OUT EVENTS FOR OLD UNIT

        QString *descript2(new QString);
        QTextStream ss2(descript2);

        memberList2 = membersMoving->getSelectedModels();

        while (!(memberList2.isEmpty())) {
            MemberModel *temp = memberList2.first();
            ss2 << "Member Name: " << temp->getFirstName() << " " << temp->getLastName() << "\n";
            if(temp->isTelephoneShared()) {
                ss2 << "Telephone Number: " << temp->getTelephoneNum() << "\n";
            }
            memberList2.removeFirst();
        }
        ss2 << "Unit Number: " << QVariant(outOfUnit->id).toString() << "\n";
        ss2 << "Move-in Date: " << moveInDate.toString("MMMM d, yyyy") << "\n";

        // Get the Inspections Committee
        CommitteeModel *ic(CommitteeModel::findById(
            CommitteeModel::INSPECTIONS_COMMITTEE_ID
        ));

        // Send First Move-Out Inspection Task
        QDateTime MoveOut_in_30_days(noticeDate);
        MoveOut_in_30_days = MoveOut_in_30_days.addDays(30);
        ic->addTask(QString("Move-out Inspection 1"), *descript2, MoveOut_in_30_days);

        // Send Second Move-Out Inspection Task
        QDateTime one_week_before(moveOutDate);
        one_week_before = one_week_before.addDays(-7);
        ic->addTask(QString("Move-out Inspection 2"), *descript2, one_week_before);

        // Send Third Move-Out Inspection Task
        QDateTime dayOf(moveOutDate);
        ic->addTask(QString("Move-out Inspection 3"), *descript2, dayOf);

    }

    done(QDialog::Accepted);
}

/**
  * When the options are cancelled
  */

void TriggerInternalMoveView::cancelEvent(void){
    done(QDialog::Rejected);
}
