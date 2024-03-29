#ifndef TRIGGERMOVEOUTVIEW_H
#define TRIGGERMOVEOUTVIEW_H

#include <QWidget>
#include <QDialog>
#include <QTextStream>
#include <QLineEdit>
#include <QDateEdit>
#include <QDateTime>
#include <QRadioButton>
#include <QPushButton>
#include <QMessageBox>
#include <QCheckBox>

#include "lib/gui/modellistwidget.h"
#include "lib/gui/formlayoutptr.h"

#include "model/membermodel.h"
#include "model/committeemodel.h"
#include "model/taskmodel.h"

class TriggerMoveOutView : public QDialog{
    Q_OBJECT

public:
    TriggerMoveOutView(UnitModel *chosenUnit, QWidget *parent = 0);

protected:
    ModelListWidget<MemberModel> *membersMoving;
    QDateEdit *notice_date;
    QDateEdit *move_out_date;
    QPushButton *ok_button;
    QCheckBox *isEmpty;

    TaskModel *task;
    CommitteeModel *committee;
    QList<MemberModel*> memberList;
    MemberModel *member;
    UnitModel *unitNo;

public slots:
    bool checkDate(void);
    void tryOK(void);
    void activateEmptyUnit (void);
    void okEvent(void);
    void cancelEvent(void);

};

#endif // TRIGGERMOVEOUTVIEW_H
