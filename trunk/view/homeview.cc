/*
 * ui_cooper.cc
 *
 *  Created on: Mar 6, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "view/homeview.h"

/**
 * Constructor, make the UI.
 */
HomeView::HomeView(void) {
    QTabWidget *tabs(new QTabWidget);

    PermissionModelSet committee_tab_perms(
        ADD_TASK | EDIT_TASK | DELETE_TASK | ADD_COMMITTEE |
        EDIT_COMMITTEE | DELETE_COMMITTEE | PRINT_COMMITTEE_LIST
    );

    PermissionModelSet member_tab_perms(
        ADD_MEMBER | MOVE_MEMBER | EDIT_MEMBER_INFO | EDIT_MEMBER_STATUS |
        DELETE_MEMBER | INIT_MEMBER_COMMITTEE | EDIT_MEMBER_COMMITTEE |
        PRINT_PUBLIC_LIST | PRINT_PRIVATE_LIST
    );

    if(active_user->hasPermission(member_tab_perms)) {
        tabs->addTab(new ControlMemberView(tabs), "Member");
    }

    if(active_user->hasPermission(committee_tab_perms)) {
        tabs->addTab(new ControlCommitteeView(tabs), "Committee");
    }

    // such "feature testing" should not be done often
    if(!active_user->is_coordinator
    && active_user->hasPermission(VIEW_SELF_INFO)) {
        tabs->addTab(new ViewMemberView(
            static_cast<MemberModel *>(active_user),
            tabs
        ), "My Info");
    }

    makeMenuBar();
    setContentsMargins(11, 11, 11, 11);
    setCentralWidget(tabs);
    connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged()));
}

/**
 * Create the menu bar.
 */
void HomeView::makeMenuBar(void) {
    QMenu *file_menu = menuBar()->addMenu("&File");
    (void) file_menu;
    QMenu *print_menu = menuBar()->addMenu("&Print");
    print_phone_public = print_menu->addAction("Print Public Phone List");
    print_phone_all = print_menu->addAction("Print Full Phone List");
    print_committee = print_menu->addAction("Print Committee List");
    print_task = print_menu->addAction("Print Pending Tasks");
}

/**
 * Close evebt for the home window.
 */
void HomeView::closeEvent(QCloseEvent *event) {
    Database::disconnect();
    QMainWindow::closeEvent(event);
}

void HomeView::pageChanged(int index){

    QTabWidget *tab = dynamic_cast<QTabWidget *>(QObject::sender());
    QString labeltxt = tab->tabText(index);
    if(labeltxt == "Member"){
        print_phone_public->setVisible(true);
        print_phone_all->setVisible(true);
        print_committee->setVisible(false);
        print_task->setVisible(false);
        if(active_user->hasPermission(PRINT_PRIVATE_LIST)){
            print_phone_public->setVisible(true);
            print_phone_all->setVisible(true);
        }else if(active_user->hasPermission(PRINT_PUBLIC_LIST)) {
            print_phone_public->setVisible(true);
            print_phone_all->setVisible(false);
        }else {
            print_phone_public->setVisible(false);
            print_phone_all->setVisible(false);
        }
    }
    if(labeltxt == "Committee"){
        print_phone_public->setVisible(false);
        print_phone_all->setVisible(false);
        print_committee->setVisible(true);
        print_task->setVisible(true);
    }


}

