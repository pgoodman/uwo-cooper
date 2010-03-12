/*
 * viewmemberview.cc
 *
 *  Created on: Mar 12, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "view/viewmemberview.h"

ViewMemberView::ViewMemberView(MemberModel *member, QWidget *parent)
 : QWidget(parent) {
    FormLayoutPtr layout(this);

    QDateTime date;
    date.setTime_t(member->getMoveInTime());

    stringstream money_ss;
    money_ss << "$" << member->getMoneyOwed();

    layout << "First Name: " | member->getFirstName();
    layout << "Last Name: " | member->getLastName();
    layout << "Pre-co-op address: " | member->getAddress();
    layout << "Move-in Date: " | date.toString("MMMM d, yyyy");
    layout << "Balance Owed: " | QString(money_ss.str().c_str());

}
