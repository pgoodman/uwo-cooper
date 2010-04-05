#include "view/memberswapview.h"

MemberSwapView::MemberSwapView(CommitteeModel *currentCommittee, QWidget *parent)
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

void MemberSwapView::setUpLayout()
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

void MemberSwapView::addMember()
{
    if(membersNot->getSelectedModel() != 0)
    {
        MemberModel *member = membersNot->getSelectedModel();

        membersIn->addModel(member);
        membersNot->removeModel(member);
 //       updateListModels();
    }
    else
    {
        return;
    }
}

void MemberSwapView::removeMember()
{
    if(membersIn->getSelectedModel() != 0)
    {

       MemberModel *member = membersIn->getSelectedModel();

       membersIn->removeModel(member);
       membersNot->addModel(member);

//       updateListModels();

    }
    else
    {
        return;
    }
}


void MemberSwapView::updateListModels()
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

void MemberSwapView::saveLists()
{
       QList<MemberModel *> membsIn = membersIn->getModels();
       QList<MemberModel *> membsNot = membersNot->getModels();

       MemberModel *mems;

       while(membsIn.size() != 0)
       {
           mems = membsIn.takeLast();
           if(mems->getCommitteeId() != committee->id)
           {
               mems->setCommittee(committee);
               mems->save();
           }
       }

       while(membsNot.size() != 0)
       {
           mems = membsNot.takeLast();
           if(mems->getCommitteeId() == committee->id)
           {
               mems->setCommittee(0);
               mems->save();
           }
       }
}
