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

    QGridLayout *layout(new QGridLayout(this));
    QPushButton *cancel(new QPushButton("Close", this));
    setLayout(layout);

    // add in the add form
    AddDependantView *adder(new AddDependantView(member, this));
    layout->addWidget(adder);

    connect(cancel, SIGNAL(clicked()), this, SLOT(accept()));
    connect(
        adder, SIGNAL(dependantAdded(DependantModel *)),
        this, SLOT(addDependantToList(DependantModel *))
    );

    QScrollArea *list(new QScrollArea(this));
    list->setWidgetResizable(true);
    QWidget *dependant_widget(new QWidget(list));
    layout->addWidget(list);
    list_layout = new QGridLayout(dependant_widget);
    dependant_widget->setLayout(list_layout);

    // add in the list of dependants
    DependantModel::iterator_range dependants(user->findDependants());
    DependantModel::iterator it(dependants.first), end(dependants.second);
    for(; it != end; it++) {
        DependantListItemView *item(new DependantListItemView(
            *it,
            dependant_widget
        ));
        list_layout->addWidget(item);

        connect(
            item, SIGNAL(dependantRemoved(DependantListItemView *)),
            this, SLOT(removeDependantFromList(DependantListItemView *))
        );
    }

    list->setWidget(dependant_widget);
    layout->addWidget(cancel);
}
/**
 * Remove a dependant list item view from the list.
 */
void DependantListView::removeDependantFromList(DependantListItemView *item) {
    list_layout->removeWidget(item);
    delete item;
}

/**
 * Add a dependant to the list.
 */
void DependantListView::addDependantToList(DependantModel *dep) {
    DependantListItemView *item(new DependantListItemView(dep, this));
    list_layout->addWidget(item);
}
