#include "editcommitteeview.h"

EditCommitteeView::EditCommitteeView(CommitteeModel *selectedCommittee, 
                                     QWidget *parent) : QDialog(parent) {

    FormLayoutPtr layout(this);

    selCommittee = selectedCommittee;

    //layout
    committeeName = layout << "Committee Name: " |= new QLineEdit(selCommittee->getName());
    selectChair = layout << "Select a Chair" |= new ModelListWidget<MemberModel>;
    selectSecretary = layout << "Select a Secretary" |= new ModelListWidget<MemberModel>;


    memList = new PermListWidget(QString("Member Permissions"), selCommittee->getMemPerms());
    chairList = new PermListWidget(QString("Chair Permissions"), selCommittee->getChairPerms());

    QTabWidget *tabs = new QTabWidget;

    tabs->addTab(memList, "Member Permissions");
    tabs->addTab(chairList, "Chair Permissions");

    layout << "" | tabs;

    //Add / cancel buttons
    QPushButton *editButton = new QPushButton("Edit Committee");
    QPushButton *cancelButton = new QPushButton("Cancel");

    layout << editButton | cancelButton;

    setModal(true);
    setWindowTitle("Edit Committee");
    selectChair->fill(&MemberModel::findAll);
    selectSecretary->fill(&MemberModel::findAll);

    if(selCommittee->getChair() != 0)
    {
    selectChair->selectModel(selCommittee->getChair());
    }
    else
    {
        selectChair->selectFirst();
    }

    if(selCommittee->getSec() != 0){
        selectSecretary->selectModel(selCommittee->getSec());
    }
    else
    {
        selectSecretary->selectFirst();
    }

    //Connect slots/signals
    connect(editButton, SIGNAL(clicked()), this, SLOT(editCommittee()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelCommittee()));

}

EditCommitteeView::~EditCommitteeView(){}


//Function called when edit committee button is pushed
void EditCommitteeView::editCommittee()
{
    MemberModel *chairModel = selectChair->getModel();
    MemberModel *secModel = selectSecretary->getModel();

    selCommittee->setName(committeeName->text());
    selCommittee->setChairPerms(chairList->getPermissions());
    selCommittee->setMemberPerms(memList->getPermissions());
    selCommittee->setChair(chairModel);
    selCommittee->setSecretary(secModel);

    selCommittee->save();

    chairModel->setCommittee(selCommittee);
    chairModel->save();

    secModel->setCommittee(selCommittee);
    secModel->save();

    done(QDialog::Accepted);
}

void EditCommitteeView::cancelCommittee()
{
    done(QDialog::Rejected);
}
