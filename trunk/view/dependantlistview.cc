/*
 * dependantlistview.cc
 *
 *  Created on: Mar 14, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "view/dependantlistview.h"

/**
 * Constructor, make the list.
 */
DependantListView::DependantListView(MemberModel *user, QWidget *parent)
 : QDialog(parent), member(user) {

    setModal(true);
    setWindowTitle("Manage Dependants");

    layout = new QGridLayout(this);
    QPushButton *cancel(new QPushButton("Cancel", this));
    setLayout(layout);

    DependantModel::iterator_range dependants(user->findDependants());
    DependantModel::iterator it(dependants.first), end(dependants.second);
    for(; it != end; it++) {
        DependantListItemView *item(new DependantListItemView(*it, this));
        items.push_back(item);
        layout->addWidget(item);

        connect(
            item, SIGNAL(dependantRemoved(DependantListItemView *)),
            this, SLOT(removeDependantFromList(DependantListItemView *))
        );
    }

    AddDependantView *adder(new AddDependantView(this));
    layout->addWidget(adder);
    layout->addWidget(cancel);

    connect(cancel, SIGNAL(clicked()), this, SLOT(accept()));
    connect(
        adder, SIGNAL(dependantAdded(DependantModel *)),
        this, SLOT(addDependantToList(DependantModel *))
    );
}
/**
 * Remove a dependant list item view from the list.
 */
void DependantListView::removeDependantFromList(DependantListItemView *item) {
    layout->removeWidget(item);
    delete item;
}

/**
 * Add a dependant to the list.
 */
void DependantListView::addDependantToList(DependantModel *dep) {
    (void) dep;
}
