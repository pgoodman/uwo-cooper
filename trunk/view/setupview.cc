/*
 * setup.cc
 *
 *  Created on: Mar 5, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#include "view/setupview.h"

/**
 * Setup wizard for the co-op.
 */
SetupView::SetupView(QWidget *parent)
 : QWizard(parent), page1(0), page2(0) {
    setWindowTitle("Cooper Setup");
    this->setWizardStyle(QWizard::ModernStyle);

    setOptions(QWizard::CancelButtonOnLeft);
    setOptions(QWizard::NoBackButtonOnLastPage);

    if(!CoordinatorModel::exists()) {
        coordinator();
    }
    units();
}

/**
 * Destructor.
 */
SetupView::~SetupView(void) { }

/**
 * Set up the coordinator of the co-op.
 */
void SetupView::coordinator(void) {

    page1 = new QWizardPage;
    QGridLayout *layout = new QGridLayout;
    page1->setLayout(layout);

    //page1->setTitle("Step 1 of 2: Coordinator Account");
    page1->setTitle("Setup Wizard");
    page1->setSubTitle("Step 1 of 2: Coordinator Account");
   //     "Please create the account name and password for the coordinator."
   // );
    setPixmap(QWizard::WatermarkPixmap, QPixmap("../images/watermark.jpg"));
    setPixmap(QWizard::BannerPixmap, QPixmap("../images/flower.jpg"));
    
    QLabel *intro = new QLabel ("Please create the account name and password for the coordinator.");
    intro->setWordWrap(true);
    QLabel *nameLabel = new QLabel("Account &Name: ");
    QLabel *passLabel = new QLabel("&Password: ");
    QLineEdit *nameLineEdit = new QLineEdit;
    coord_pass = new QLineEdit;


    nameLineEdit->setText(QString(COORDINATOR_USER_NAME));
    nameLineEdit->setReadOnly(true);

    nameLabel->setBuddy(nameLineEdit);
    passLabel->setBuddy(coord_pass);

    layout->addWidget(intro,0,0,1,2);
    layout->addWidget(nameLabel, 1,0,1,1);
    layout->addWidget(nameLineEdit,1,1,1,1);
    layout->addWidget(passLabel, 2,0,1,1);
    layout->addWidget(coord_pass,2,1,1,1);
    /*layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(passLabel, 1, 0);
    layout->addWidget(coord_pass, 1, 1);*/


    addPage(page1);
}

/**
 * Set up the units in the co-op.
 */
void SetupView::units(void) {
    page2 = new QWizardPage;
    page2->setTitle("Setup Wizard");
    page2->setSubTitle("Step 2 of 2: Initial Data File");
    //page2->setSubTitle("Please specify the initial data file name.");

    setPixmap(QWizard::WatermarkPixmap, QPixmap("../images/watermark.jpg"));
    setPixmap(QWizard::BannerPixmap, QPixmap("../images/flower.jpg"));

    QGridLayout *layout = new QGridLayout;
    page2->setLayout(layout);

    QLabel *intro = new QLabel("Please specify the initial data file name.");
    intro->setWordWrap(true);
    QLabel *fileNameLabel = new QLabel("Data &File:");
    file_name = new QLineEdit;
    QPushButton *browseFileButton = new QPushButton("Browse");

    fileNameLabel->setBuddy(file_name);

    layout->addWidget(intro,0,0,1,2);
    layout->addWidget(fileNameLabel, 1,0,1,1);
    layout->addWidget(file_name, 1,1,1,1);
    layout->addWidget(browseFileButton, 2,0,1,1);

    connect(browseFileButton, SIGNAL(clicked()), this, SLOT(browseDataFile()));

    addPage(page2);
}

/**
 * Create a file browser for findind the data file.
 */
void SetupView::browseDataFile(){
    QFileDialog *fileDialog = new QFileDialog();
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    if(fileDialog->exec() && !fileDialog->selectedFiles().isEmpty()) {
        file_name->setText(fileDialog->selectedFiles().first());
    }
}

/**
 * Validate the current page.
 */
bool SetupView::validateCurrentPage(void) {
    if(page1 == currentPage()) {
        QString password(coord_pass->text());
        if(password.isEmpty()) {
            QMessageBox::warning(
                this,
                "Empty Form Field",
                "Please insert a password."
            );
            return false;
        }
        CoordinatorModel::create(password);
    } else {
        QString path(file_name->text());
        if(path.isEmpty()) {
            QMessageBox::warning(
                this,
                "Empty Form Field",
                "Please choose a file to load."
            );
            return false;
        }
        if(!SetupController::loadData(path)) {
            return false;
        }
        
        UserModel::setActive(CoordinatorModel::load());
    }

    return true;
}
