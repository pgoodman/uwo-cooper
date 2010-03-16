/*
 * triggermoveoutview.cc
 *
 *  Created on: Mar 14, 2010
 *      Author: Stephan Beltran
 *     Version: $Id$
 */

#include "triggermoveoutview.h"

TriggerMoveOutView::TriggerMoveOutView (MemberModel *chosenMember,
                                        QWidget *parent) : QDialog(parent) {
    FormLayoutPtr layout(this);

    member = chosenMember;
    // make the layout of the form
    first_name = layout << "First Name: " |= new QLineEdit;
    last_name = layout << "Last Name: " |= new QLineEdit;
    user_name = layout << "Login Name: " |= new QLineEdit;
    unit = layout << "Unit: " |= new QLineEdit;
    move_out_date = layout << "Move Out Date: " |= new QDateEdit;
    notice_date = layout << "Notice Date: " |= new QDateEdit;
    isEmpty = layout << "Empty Unit After Move?" |= new QCheckBox;

    // make and add in the buttons
    ok_button = new QPushButton("Ok");
    QPushButton *cancel(new QPushButton("Cancel"));\
    layout << ok_button | cancel;

    // misc
    first_name->setText(member->getFirstName());
    first_name->setEnabled(false);
    last_name->setText(member->getLastName());
    last_name->setEnabled(false);
    user_name->setText(member->getUserName());
    user_name->setEnabled(false);
    unitNo = member->findUnit();
    unit->setText(QVariant(unitNo->id).toString());
    unit->setEnabled(false);
    move_out_date->setCalendarPopup(true);
    notice_date->setCalendarPopup(true);

    setModal(true);
    setWindowTitle("Trigger Move Out event");

    // signals / slots
    connect(ok_button, SIGNAL(clicked()), this, SLOT(okEvent()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelEvent()));
}

void TriggerMoveOutView::okEvent(void) {

    QDateTime moveOutDate = move_out_date->dateTime();
    QDateTime noticeDate = notice_date->dateTime();

    if (isEmpty->isChecked() == true) {
        QString *description(new QString);
        QTextStream ss(description);
        ss << "Member Name: " << member->getFirstName() << " " << member->getLastName() << "\n";
        if(member->isTelephoneShared()) {
            ss << "Telephone Number: " << member->getTelephoneNum() << "\n";
        }
        ss << "Unit Number: " << unit->text() << "\n";
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

void TriggerMoveOutView::cancelEvent(void){
    done(QDialog::Rejected);
}
