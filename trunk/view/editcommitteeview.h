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
#include "lib/gui/formlayoutptr.h"
#include "lib/gui/memberswapwidget.h"

#include "model/membermodel.h"
#include "model/committeemodel.h"
#include "model/permissionmodel.h"

#include "view/permlistview.h"

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

    ModelListWidget<MemberModel> *selectChair;
    ModelListWidget<MemberModel> *selectSecretary;
    PermListView *memList;
    PermListView *chairList;
    MemberSwapWidget *swap;

   CommitteeModel *selCommittee;

};


#endif // EDITCOMMITTEEVIEW_H
