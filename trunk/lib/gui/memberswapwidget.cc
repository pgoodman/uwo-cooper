#include "memberswapwidget.h"

MemberSwapWidget::MemberSwapWidget(CommitteeModel *currentCommittee, QWidget *parent)
    : QStackedWidget(parent)
{
    boxGroup = new QGroupBox("Member Swaping");
    committee = currentCommittee;

    layout = new QGridLayout;

    setUpLayout();
    updateListModels();

    boxGroup->setLayout(layout);
    addWidget(boxGroup);
}

void MemberSwapWidget::setUpLayout()
{
    QPushButton *addButton = new QPushButton("Add");
    QPushButton *removeButton = new QPushButton("Remove");
    QLabel *memberInLabel = new QLabel("Members In Committee");
    QLabel *memberNotLabel = new QLabel("Members Not In Committee");

    membersNot = new ModelListWidget<MemberModel>;
    membersIn = new ModelListWidget<MemberModel>;

    layout->addWidget(memberNotLabel, 0, 0);
    layout->addWidget(memberInLabel, 0, 1);
    layout->addWidget(membersNot, 1, 0);
    layout->addWidget(membersIn, 1, 1);
    layout->addWidget(addButton, 2, 0);
    layout->addWidget(removeButton, 2, 1);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addMember()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeMember()));

}

void MemberSwapWidget::addMember()
{
    if(membersNot->getSelectedModel() != 0)
    {
        MemberModel *member = membersNot->getSelectedModel();

        member->setCommittee(committee);
        member->save();

        updateListModels();
    }
    else
    {
        return;
    }
}

void MemberSwapWidget::removeMember()
{
    if(membersIn->getSelectedModel() != 0)
    {
        int ret(QMessageBox::question(this,
            "Please Confirm",
            "Are you sure you want to remove this member from this committee?",
            QMessageBox::Yes,
            QMessageBox::No
        ));
        if(QMessageBox::Yes == ret) {
            MemberModel *member = membersIn->getSelectedModel();

            member->setCommittee(0);
            member->save();
            updateListModels();
        }
    }
    else
    {
        return;
    }
}

void MemberSwapWidget::updateListModels()
{
    stringstream searchForIn;
    stringstream searchForNot;
    int id = committee->id;

    searchForIn << "committee_id=" << id;
    searchForNot << "committee_id!=" << id;

    MemberModel::iterator_range memIn(MemberModel::findAll(searchForIn.str().c_str()));
    MemberModel::iterator_range memNot(MemberModel::findAll(searchForNot.str().c_str()));

    membersNot->fill(memNot);
    membersIn->fill(memIn);
}
