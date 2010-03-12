#ifndef ADDCOMMITTEEVIEW_H
#define ADDCOMMITTEEVIEW_H

#include <ctime>

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QMessageBox>

#include "lib/gui/modellistwidget.h"
#include "lib/gui/formlayoutptr.h"

#include "model/membermodel.h"
#include "model/committeemodel.h"

class AddCommitteeView : public QDialog{
    Q_OBJECT

public:
    AddCommitteeView(QWidget *parent = 0);
    ~AddCommitteeView();

public slots:
    void addCommittee();
    void cancelCommittee();

private:
    QLineEdit *committeeName;
    QRadioButton *canDelete;

    ModelListWidget<MemberModel> *selectChair;
    ModelListWidget<MemberModel> *selectSecretary;

};


#endif // ADDCOMMITTEEVIEW_H
