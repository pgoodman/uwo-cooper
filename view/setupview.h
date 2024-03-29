/*
 * setup.h
 *
 *  Created on: Mar 5, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef SETUP_H_
#define SETUP_H_

#include <QWidget>
#include <QWizard>
#include <QWizardPage>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "model/coordinatormodel.h"

#include "controller/setupcontroller.h"

/**
 * A Wizard to go through and initialize the system.
 */
class SetupView : public QWizard {
    Q_OBJECT
public:

    SetupView(QWidget *parent = 0);
    ~SetupView();

    virtual bool validateCurrentPage(void);

protected:
    void coordinator(void);
    void units(void);

private:
    QLineEdit *coord_pass;
    QLineEdit *file_name;

    QWizardPage *page1;
    QWizardPage *page2;

private slots:
    void browseDataFile();
};

#endif /* SETUP_H_ */
