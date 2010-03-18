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

#include "lib/gui/modellistwidget.h"
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

    QRadioButton *addMemPerm;
    QRadioButton *moveMemPerm;
    QRadioButton *editMemInfoPerm;
    QRadioButton *editMemStatus;
    QRadioButton *deleteMemPerm;
    QRadioButton *initMemCommPerm;
    QRadioButton *editMemCommPerm;
    QRadioButton *addCommPerm;
    QRadioButton *editCommPerm;
    QRadioButton *deleteCommPerm;
    QRadioButton *printPrivListPerm;
    QRadioButton *printPubListPerm;
    QRadioButton *printCommListPerm;
    QRadioButton *addTaskPerm;
    QRadioButton *editTaskPerm;
    QRadioButton *deleteTaskPerm;
    QRadioButton *printTaskListPerm;
    QRadioButton *addTaskSpec;
    QRadioButton *editTaskSpecPerm;
    QRadioButton *deleteTaskSpecPerm;
    QRadioButton *actTaskSpecPerm;
    QRadioButton *editCommChairPerm;
    QRadioButton *editCommSecPerm;
    QRadioButton *viewSelfInfoPerm;
    QRadioButton *viewOhterInfoPerm;
    QRadioButton *editSelfPassPerm;



    void setUpPermissionButtons(FormLayoutPtr *layout);
    void setUpPermButton(QRadioButton *perm, const char *mess, FormLayoutPtr *layout);

   CommitteeModel *selCommittee;

};


#endif // EDITCOMMITTEEVIEW_H
