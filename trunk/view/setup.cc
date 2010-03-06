/*
 * setup.cc
 *
 *  Created on: Mar 5, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "setup.h"

/**
 * Setup wizard for the co-op.
 */
Setup::Setup(QWidget *parent)
 : QWizard(parent), page1(0), page2(0) {
    if(!Coordinator::exists()) {
        coordinator();
    }
    units();
}

/**
 * Destructor.
 */
Setup::~Setup(void) { }

/**
 * Set up the coordinator of the co-op.
 */
void Setup::coordinator(void) {

    page1 = new QWizardPage(this);
    QGridLayout *layout = new QGridLayout;
    page1->setLayout(layout);

    page1->setTitle("Step 1 of 2: Coordinator Account");
    page1->setSubTitle(
        "Please create the account name and password for the coordinator."
    );

    QLabel *nameLabel = new QLabel("Account &Name: ");
    QLabel *passLabel = new QLabel("&Password: ");
    QLineEdit *nameLineEdit = new QLineEdit;
    coord_pass = new QLineEdit;


    nameLineEdit->setText(QString(COORDINATOR_USER_NAME));
    nameLineEdit->setReadOnly(true);

    nameLabel->setBuddy(nameLineEdit);
    passLabel->setBuddy(coord_pass);

    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(passLabel, 1, 0);
    layout->addWidget(coord_pass, 1, 1);

    setPage(1, page1);
}

/**
 * Set up the units in the co-op.
 */
void Setup::units(void) {

    page2 = new QWizardPage(this);
    page2->setTitle("Step 2 of 2: Initial Data File");
    page2->setSubTitle("Please specify the initial data file name.");

    QGridLayout *layout = new QGridLayout;
    page2->setLayout(layout);

    QLabel *fileNameLabel = new QLabel("Data &File:");
    file_name = new QLineEdit;
    QPushButton *browseFileButton = new QPushButton("Browse");

    fileNameLabel->setBuddy(file_name);

    layout->addWidget(fileNameLabel, 0, 0);
    layout->addWidget(file_name, 1, 0);
    layout->addWidget(browseFileButton, 1, 1);

    connect(browseFileButton, SIGNAL(clicked()), this, SLOT(browseDataFile()));

    setPage(2, page2);
}

/**
 * Create a file browser for findind the data file.
 */
void Setup::browseDataFile(){
    QFileDialog *fileDialog = new QFileDialog();
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    if(fileDialog->exec() && !fileDialog->selectedFiles().isEmpty()) {
        file_name->setText(fileDialog->selectedFiles().first());
    }
}

/**
 * Validate the current page.
 */
bool Setup::validateCurrentPage(void) {
    if(page1 == currentPage()) {
        QString password(coord_pass->text());
        if(password.isEmpty()) {
            //page1_error
            return false;
        }

        Coordinator::create(password);
        removePage(1);
    } else {
        QString path(file_name->text());
        if(path.isEmpty()) {
            return false;
        }
        return SetupController::loadData(path);
    }

    return true;
}
