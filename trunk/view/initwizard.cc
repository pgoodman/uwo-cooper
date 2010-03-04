#include <QtGui>
#include "initwizard.h"
#include "../controller/setupcontroller.h"
#include "../controller/usercontroller.h"
#include "../datatype/user.h"
#include "../datatype/coordinator.h"
#include "../conf.h"

InitWizard::InitWizard(QWidget *parent)
    : QWizard(parent)
{
    setPage(Page_Account, new AccountPage);
    setPage(Page_Datafile, new DatafilePage);
    setPage(Page_Conclusion, new ConclusionPage);
    setGeometry(0,0,400,300);
    setModal(true);
    if(!Coordinator::exists())
        setStartId(Page_Account);
    else
        setStartId(Page_Datafile);

    //setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

    setWindowTitle(tr("Cooper Initialization Wizard"));
}

AccountPage::AccountPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Step 1 of 2: Coordinator Account"));
    //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));
    setSubTitle(tr("Please create the account name and password for the coordinator."));

    nameLabel = new QLabel(tr("Account &Name: "));
    pwdLabel=new QLabel(tr("&Password"));
    nameLineEdit=new QLineEdit;
    nameLineEdit->setText(new QString(COORDINATOR_USER_NAME));
    nameLineEdit->setReadOnly(true);
    pwdLineEdit=new QLineEdit;
    nameLabel->setBuddy(nameLineEdit);
    pwdLabel->setBuddy(pwdLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(pwdLabel, 1, 0);
    layout->addWidget(pwdLineEdit, 1, 1);

    registerField("coordinator.name*",nameLineEdit);
    registerField("coordinator.pwd",pwdLineEdit);

    setLayout(layout);
}

int AccountPage::nextId() const
{
    return InitWizard::Page_Datafile;
}

DatafilePage::DatafilePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Step 2 of 2: Initial Data File"));
    setSubTitle(tr("Please specify the initial data file name."));

    fileNameLabel = new QLabel(tr("Data &File:"));
    fileNameLineEdit = new QLineEdit;
    fileNameLabel->setBuddy(fileNameLineEdit);
    browseFileButton = new QPushButton("Browse");

    registerField("datafile.name*", fileNameLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(fileNameLabel, 0, 0);
    layout->addWidget(fileNameLineEdit, 1, 0);
    layout->addWidget(browseFileButton, 1, 1);
    setLayout(layout);
    connect(browseFileButton,SIGNAL(clicked()),this,SLOT(browseDataFile()));

}

void DatafilePage::browseDataFile(){
    QFileDialog *fileDialog =new QFileDialog();
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    if(fileDialog->exec()){
        if (!fileDialog->selectedFiles().isEmpty()) {
            fileNameLineEdit->setText(fileDialog->selectedFiles().first());
         }
     }
}

int DatafilePage::nextId() const
{
    return InitWizard::Page_Conclusion;
}

ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    std::string name= std::string(this->field("coordinator.name").toString().toStdString());
    std::string pwd= std::string(this->field("coordinator.pwd").toString().toStdString());
    //creating coordinator account
    if(!ConclusionPage::initAccount(name,pwd)){
        std::string filename = std::string(this->field("datafile.name").toString().toStdString());

        if(!ConclusionPage::initData(filename)){
            setTitle(tr("Initialization Completed"));
            //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

            conclusionLabel = new QLabel(tr("You have successfully initialized Cooper. "
                                         "You are now logged in as the coordinator."));
            conclusionLabel->setWordWrap(true);
            //set active user
            UserController::login(name, pwd);
        }
        else{
            setTitle(tr("Initialization Failed"));
            //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

            conclusionLabel = new QLabel(tr("The data file cannot be loaded. Please try again."));
            conclusionLabel->setWordWrap(true);
        }

    }
    else {
        setTitle(tr("Initialization Failed"));
        //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

        conclusionLabel = new QLabel(tr("The account creation failed. Please try again."));
        conclusionLabel->setWordWrap(true);
    }

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(conclusionLabel);
    setLayout(layout);
}

int ConclusionPage::initAccount(std::string name, std::string pwd){
    //return SetupController::addCoordinator(name,pwd);
    Coordinator::create(name, pwd);
    return 1;
}

int ConclusionPage::initData(std::string filename) {
    SetupController::loadData(filename);
    return 1;
}

int ConclusionPage::nextId() const
{
    return -1;
}

