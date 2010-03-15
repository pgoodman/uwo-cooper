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
    TriggerMoveOutView(MemberModel *chosenMember, QWidget *parent = 0);

protected:
    QLineEdit *first_name;
    QLineEdit *last_name;
    QLineEdit *user_name;
    QLineEdit *unit;
    QDateEdit *notice_date;
    QDateEdit *move_out_date;
    QPushButton *ok_button;
    QCheckBox *isEmpty;

    TaskModel *task;
    CommitteeModel *committee;
    MemberModel *member;
    UnitModel *unitNo;

public slots:
    void okEvent(void);
    void cancelEvent(void);

};

#endif // TRIGGERMOVEOUTVIEW_H
