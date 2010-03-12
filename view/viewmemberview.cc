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

    QDateTime date(member->getMoveInTime());

    stringstream money_ss;
    money_ss << "$" << member->getMoneyOwed();

    layout << "First Name: " | member->getFirstName();
    layout << "Last Name: " | member->getLastName();
    layout << "Pre-co-op address: " | member->getAddress();
    layout << "Telephone Number: " | member->getTelephoneNum();
    layout << "Move-in Date: " | date.toString("MMMM d, yyyy");
    layout << "Balance Owing to Co-op: " | QString(money_ss.str().c_str());
    layout << "Login Name: " | member->getLoginName();
    layout << "Password: " | member->getPassword();
}
