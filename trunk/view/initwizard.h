#ifndef INITWIZARD_H
#define INITWIZARD_H

#include <string>

#include <QtGui>
#include <QWizard>

#include "conf.h"
#include "controller/setupcontroller.h"
#include "controller/usercontroller.h"
#include "datatype/user.h"
#include "datatype/coordinator.h"
#include "window.h"

 class InitWizard : public QWizard
 {
     Q_OBJECT

 public:
     enum { Page_Account, Page_Datafile, Page_Conclusion };
     InitWizard(QWidget *parent = 0);
 };

 class AccountPage : public QWizardPage
 {
     Q_OBJECT

 public:
     AccountPage(QWidget *parent = 0);
     int nextId() const;

 private:
     QLabel *nameLabel;
     QLabel *pwdLabel;
     QLineEdit *nameLineEdit;
     QLineEdit *pwdLineEdit;
 };

 class DatafilePage : public QWizardPage
 {
     Q_OBJECT

 public:
     DatafilePage(QWidget *parent = 0);
     int nextId() const;

 private slots:
     void browseDataFile();

 private:
     QLabel *fileNameLabel;
     QLineEdit *fileNameLineEdit;
     QPushButton *browseFileButton;
 };

 class ConclusionPage : public QWizardPage
 {
     Q_OBJECT

 public:
     ConclusionPage(QWidget *parent = 0);
     int nextId() const;
     //int initAccount(std::string name, std::string pwd);
     //int initData(std::string filename);

  private:
     QLabel *conclusionLabel;
     void initializePage();

 };

#endif // SETUPWIZARD_H
