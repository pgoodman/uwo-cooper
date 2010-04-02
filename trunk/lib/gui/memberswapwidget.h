#ifndef MEMBERSWAPWIDGET_H
#define MEMBERSWAPWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QStackedWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QList>

#include "model/membermodel.h"
#include "model/committeemodel.h"
#include "modellistwidget.h"

class MemberSwapWidget : public QStackedWidget{
Q_OBJECT

public:
    MemberSwapWidget(CommitteeModel *curCommittee, QWidget *parent = 0);

    void saveLists();

public slots:
    void addMember();
    void removeMember();

private:
    QGridLayout *layout;
    QGroupBox *boxGroup;

    ModelListWidget<MemberModel> *membersNot;
    ModelListWidget<MemberModel> *membersIn;

    CommitteeModel *committee;

    void setUpLayout();
    void updateListModels();

};

#endif // MEMBERSWAPWIDGET_H
