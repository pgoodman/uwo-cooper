/*
 * triggermoveoutview.cc
 *
 *  Created on: Mar 14, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "triggermoveoutview.h"

/**
  * Constructor
  */

TriggerMoveOutView::TriggerMoveOutView (UnitModel *chosenUnit,
                                        QWidget *parent) : QDialog(parent) {
    // Set up the form layout
    FormLayoutPtr layout(this);

    // Get the unit being moved out of
    unitNo = chosenUnit;

    // make the layout of the form
    membersMoving = layout << "Choose the members moving out: " |= new ModelListWidget<MemberModel>;
    move_out_date = layout << "Move Out Date: " |= new QDateEdit;
    notice_date = layout << "Notice Date: " |= new QDateEdit;
    isEmpty = layout << "Empty Unit After Move?" |= new QCheckBox;

    // make and add in the buttons
    ok_button = new QPushButton("Ok");
    QPushButton *cancel(new QPushButton("Cancel"));\
    layout << ok_button | cancel;

    // misc
    std::stringstream ss;
    ss << "id != " << (unitNo->id);
    MemberModel::iterator_range memberList(MemberModel::findAll(ss.str().c_str()));
    membersMoving->setMultipleSelect(true);
    membersMoving->fill(memberList);
    membersMoving->selectFirst();

    // Note: if all members are moving, then unit automatically empty, check the box
    move_out_date->setCalendarPopup(true);
    notice_date->setCalendarPopup(true);
    isEmpty->setDisabled(true);
    setModal(true);
    setWindowTitle("Trigger Move Out event");

    // signals / slots
    connect(ok_button, SIGNAL(clicked()), this, SLOT(tryOK()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelEvent()));
    connect(
        membersMoving, SIGNAL(itemSelectionChanged()),
        this, SLOT(activateEmptyUnit())
    );

}

/**
 * Attempt Check the date.
 */
bool TriggerMoveOutView::checkDate(void) {
    QDateTime today = QDateTime::currentDateTime();
    today.setTime(QTime());
    if(move_out_date->dateTime() < today) {
       QMessageBox::information(
           this, "Invalid Field",
           "Please enter a move in date that is not in the past."
       );
       return false;
    }
    else if(notice_date->dateTime() < today) {
        QMessageBox::information(
            this, "Invalid Field",
            "Please enter a move in date that is not in the past."
        );
        return false;
     }
    return true;
}

/**
 * Attempt to accept the event
 */
void TriggerMoveOutView::tryOK(void) {
    if(this->checkDate()) {
        emit okEvent();
    }
}

/**
 * De/activate the check box depending on whether all members are chosen or not
 */
void TriggerMoveOutView::activateEmptyUnit () {
    QList<MemberModel*> members(membersMoving->getSelectedModels());
    isEmpty->setChecked(membersMoving->count() == members.count());
}

/**
  * Causes the function to trigger a move out event
  */

void TriggerMoveOutView::okEvent(void) {

    // Get the information on the move out date and the notice date
    QDateTime moveOutDate = move_out_date->dateTime();
    QDateTime noticeDate = notice_date->dateTime();
    memberList = membersMoving->getSelectedModels();

    // If the unit will be empty upon move in, send approprate move tasks to the inspections committee
    if (isEmpty->isChecked() == true) {
        QString *description(new QString);
        QTextStream ss(description);

        while (!(memberList.isEmpty())) {
            MemberModel *temp = memberList.first();
            ss << "Member Name: " << temp->getFirstName() << " " << temp->getLastName() << "\n";
            if(temp->isTelephoneShared()) {
                ss << "Telephone Number: " << temp->getTelephoneNum() << "\n";
            }
            memberList.removeFirst();
        }

        ss << "Unit Number: " << unitNo->toString() << "\n";
        ss << "Move-out Date: " << moveOutDate.toString("MMMM d, yyyy") << "\n";

        // Get the Inspections Committee
        CommitteeModel *ic(CommitteeModel::findById(
            CommitteeModel::INSPECTIONS_COMMITTEE_ID
        ));


        // Send First Move-Out Inspection Task
        QDateTime in_30_days(noticeDate);
        in_30_days = in_30_days.addDays(30);
        ic->addTask(QString("Move-out Inspection 1"), *description, in_30_days);

        // Send Second Move-Out Inspection Task
        QDateTime one_week_before(moveOutDate);
        one_week_before = one_week_before.addDays(-7);
        ic->addTask(QString("Move-out Inspection 2"), *description, one_week_before);

        // Send Third Move-Out Inspection Task
        QDateTime dayOf(moveOutDate);
        ic->addTask(QString("Move-out Inspection 3"), *description, dayOf);

    }

    done(QDialog::Accepted);
}

/**
  * If options are all cancelled
  */

void TriggerMoveOutView::cancelEvent(void){
    done(QDialog::Rejected);
}
