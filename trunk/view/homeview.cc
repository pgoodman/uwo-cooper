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
}

/**
 * Create the menu bar.
 */
void HomeView::makeMenuBar(void) {
    QMenu *file_menu = menuBar()->addMenu("&File");
    (void) file_menu;
}

/**
 * Close evebt for the home window.
 */
void HomeView::closeEvent(QCloseEvent *event) {
    Database::disconnect();
    QMainWindow::closeEvent(event);
}



