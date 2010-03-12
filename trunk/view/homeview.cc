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
    tabs->addTab(new ControlMemberView(tabs), "Member");
    tabs->addTab(new ControlCommitteeView(tabs), "Committee");
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



