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

    CommitteeModel *comm(member->findCommittee());
    if(0 != comm) {
        layout << "Committee: " | comm->toString();
    }

    UnitModel *unit(member->findUnit());
    if(0 != unit) {
        layout << "Unit: " | unit->toString();
    }

    DependantModel::iterator_range deps(member->findDependants());
    DependantModel::iterator it(deps.first), end(deps.second);
    QString *dependants(new QString);
    QTextStream ss(dependants);
    bool has_any(false);
    for(QString sep(""); it != end; sep = ", ", has_any = true, it++) {
        ss << sep << (*it)->toString();
    }

    if(has_any) {
        layout << "Dependants: " | *dependants;
    }
    delete dependants;
}
