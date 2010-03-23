#ifndef EDITCOMMITTEEVIEW_H
#define EDITCOMMITTEEVIEW_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QDateTime>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QMessageBox>
#include <QTabWidget>

#include "lib/gui/modellistwidget.h"
#include "lib/gui/permlistwidget.h"
#include "lib/gui/formlayoutptr.h"

#include "model/membermodel.h"
#include "model/committeemodel.h"
#include "model/permissionmodel.h"

class EditCommitteeView : public QDialog{
    Q_OBJECT

public:
    EditCommitteeView(CommitteeModel *selectedCommittee,
                      QWidget *parent = 0);
    ~EditCommitteeView();

public slots:
    void editCommittee();
    void cancelCommittee();

private:
    QLineEdit *committeeName;
    QRadioButton *canDelete;

    ModelListWidget<MemberModel> *selectChair;
    ModelListWidget<MemberModel> *selectSecretary;
    PermListWidget *memList;
    PermListWidget *chairList;

   CommitteeModel *selCommittee;

};


#endif // EDITCOMMITTEEVIEW_H
