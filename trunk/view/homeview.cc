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
//HomeView::HomeView(QWidget *parent):QMainWindow(parent) {
HomeView::HomeView(QWidget *parent):QDialog(parent) {
    QTabWidget *tabs = new QTabWidget();
    setTabFormat(tabs);

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
        ViewMemberView * myinfo = new ViewMemberView(
                static_cast<MemberModel *>(active_user),
                tabs);

        tabs->addTab(myinfo, "My Info");
    }

    //makeMenuBar();
    //setContentsMargins(11, 11, 11, 11);
    //setCentralWidget(tabs);
    QLayout *layout = new QVBoxLayout();
    layout->addWidget(tabs);
    this->setFixedSize(tabs->size().width(),tabs->size().height());
    this->setLayout(layout);
}

/**
 * Create the menu bar.
 */
/*void HomeView::makeMenuBar(void) {
    QMenu *file_menu = menuBar()->addMenu("&System");
    //(void) file_menu;
    file_menu->addAction("Logoff",this,"&userLogoff()");
    file_menu->addAction("Exit",this,"&accept()");
}*/

/**
 * Close evebt for the home window.
 */
/*void HomeView::closeEvent(QCloseEvent *event) {
    Database::disconnect();
    QMainWindow::closeEvent(event);
}*/

void HomeView::setTabFormat(QTabWidget *qtab){
    //qtab->setFixedSize(400,320);
    qtab->setStyleSheet(
        "QTabWidget::pane {"
        "border-top: 0px solid #C2C7CB;}"
        "QTabWidget::tab-bar {left: 2px}"
        "QTabBar::tab {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
        "stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
        "border: 1px solid #C4C4C3;"
        "border-bottom-color: #C2C7CB;"
        "border-top-left-radius: 4px;"
        "border-top-right-radius: 4px;"
        "min-width: 20ex;min-height: 5ex;padding: 2px;}"
        "QTabBar::tab:selected, QTabBar::tab:hover {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "stop: 0 #fafafa, stop: 0.4 #f4f4f4,"
        "stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);}"
        "QTabBar::tab:selected {border-color: #9B9B9B;"
        "border-bottom-color: #C2C7CB;}"
        "QTabBar::tab:!selected {margin-top: 2px;}"
        "QTabBar::tab:selected {margin-left: -2px;margin-right: -2px;}"
        "QTabBar::tab:first:selected {margin-left: 0;}"
        "QTabBar::tab:last:selected {margin-right: 0;}"
        "QTabBar::tab:only-one {margin: 0;}"
    );
}
