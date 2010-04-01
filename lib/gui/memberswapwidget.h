#ifndef MEMBERSWAPWIDGET_H
#define MEMBERSWAPWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

#include "model/membermodel.h"
#include "model/committeemodel.h"
#include "modellistwidget.h"

class MemberSwapWidget : public QScrollArea{
Q_OBJECT

public:
    MemberSwapWidget(CommitteeModel *curCommittee, QWidget *parent = 0);

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
