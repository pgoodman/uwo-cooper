#ifndef TRIGGERINTERNALMOVEVIEW_H
#define TRIGGERINTERNALMOVEVIEW_H

#include <sstream>

#include <QWidget>
#include <QDialog>
#include <QTextStream>
#include <QLineEdit>
#include <QDateEdit>
#include <QDateTime>
#include <QRadioButton>
#include <QPushButton>
#include <QMessageBox>
#include <QButtonGroup>

#include "lib/gui/modellistwidget.h"
#include "lib/gui/formlayoutptr.h"

#include "model/membermodel.h"
#include "model/committeemodel.h"
#include "model/taskmodel.h"

class TriggerInternalMoveView : public QDialog{
    Q_OBJECT

public:
    TriggerInternalMoveView(MemberModel *chosenMember, QWidget *parent = 0);

protected:
    QLineEdit *first_name;
    QLineEdit *last_name;
    QLineEdit *user_name;
    QLineEdit *oldunit;
    ModelListWidget<UnitModel> *newunit;
    QDateEdit *move_in_date;
    QPushButton *ok_button;
    QRadioButton *isEmpty;
    QRadioButton *withMembers;

    TaskModel *task;
    CommitteeModel *committee;
    MemberModel *member;
    UnitModel *unitNo;

public slots:
    void okEvent(void);
    void cancelEvent(void);

};

#endif // TRIGGERINTERNALMOVEVIEW_H
