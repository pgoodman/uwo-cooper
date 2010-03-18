#include "editcommitteeview.h"

EditCommitteeView::EditCommitteeView(CommitteeModel *selectedCommittee, 
                                     QWidget *parent) : QDialog(parent) {

    FormLayoutPtr layout(this);

    selCommittee = selectedCommittee;

    //Make yes/no for can delete
    QButtonGroup *canDeleteGroup(new QButtonGroup);
    QRadioButton *cantDelete(new QRadioButton("No"));
    canDelete = new QRadioButton("Yes");
    canDeleteGroup->addButton(canDelete);
    canDeleteGroup->addButton(cantDelete);



    //layout
    committeeName = layout << "Committee Name: " |= new QLineEdit(selCommittee->getName());
    layout << "Is this Committee deleteable?" | canDelete;
    layout << "" | cantDelete;
    selectChair = layout << "Select a Chair" |= new ModelListWidget<MemberModel>;
    selectSecretary = layout << "Select a Secretary" |= new ModelListWidget<MemberModel>;

     setUpPermissionButtons(&layout);


    //Add / cancel buttons
    QPushButton *editButton = new QPushButton("Edit Committee");
    QPushButton *cancelButton = new QPushButton("Cancel");

    layout << editButton | cancelButton;

    //misc
    canDelete->setChecked(true);
    setModal(true);
    setWindowTitle("Edit Committee");
    selectChair->fill(&MemberModel::findAll);
    selectSecretary->fill(&MemberModel::findAll);

    //Connect slots/signals
    connect(editButton, SIGNAL(clicked()), this, SLOT(addCommittee()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelCommittee()));

}

EditCommitteeView::~EditCommitteeView(){}

void EditCommitteeView::editCommittee()
{

}

void EditCommitteeView::cancelCommittee()
{
    done(QDialog::Rejected);
}

void EditCommitteeView::setUpPermissionButtons(FormLayoutPtr *layout)
{
    setUpPermButton(addMemPerm, "Add Member Permission?:", layout);
    setUpPermButton(moveMemPerm, "Move Member Permission?:", layout);
    setUpPermButton(editMemInfoPerm, "Edit Member Permission?:", layout);
    setUpPermButton(editMemStatus, "Edit Member Status Permission?:", layout);
    setUpPermButton(deleteMemPerm, "Delete Member Permission?:", layout);
    setUpPermButton(initMemCommPerm, "Initialize Member Committee Permission?:", layout);
    setUpPermButton(editMemCommPerm, "Edit Member Committee Permission?:", layout);
    setUpPermButton(addCommPerm, "Add Committee Permission?:", layout);
    setUpPermButton(editCommPerm, "Edit Committee Permission?:", layout);
    setUpPermButton(deleteCommPerm, "Delete Committee Permission?:", layout);
    setUpPermButton(printPrivListPerm, "Print Private ListPermission?:", layout);
    setUpPermButton(printPubListPerm, "Print Public ListPermission?:", layout);
    setUpPermButton(printCommListPerm, "Print Committee List Permission?:", layout);
    setUpPermButton(addTaskPerm, "Add Task Permission?:", layout);
    setUpPermButton(editTaskPerm, "Edit Task Permission?:", layout);
    setUpPermButton(deleteTaskPerm, "Delete Task Permission?:", layout);
    setUpPermButton(printTaskListPerm, "Print Task List Permission?:", layout);
    setUpPermButton(addTaskSpec, "Add Task Spec Permission?:", layout);
    setUpPermButton(editTaskSpecPerm, "Edit Task Spec Permission?:", layout);
    setUpPermButton(deleteTaskSpecPerm, "Delete Task Spec Permission?:", layout);
    setUpPermButton(actTaskSpecPerm, "Activate Task Spec Permission?:", layout);
    setUpPermButton(editCommChairPerm, "Edit Committee Chair Permission?:", layout);
    setUpPermButton(editCommSecPerm, "Edit Committee Secretary Permission?:", layout);
    setUpPermButton(viewSelfInfoPerm, "View Self Info Permission?:", layout);
    setUpPermButton(viewOhterInfoPerm, "View Others Info Permission?:", layout);
    setUpPermButton(editSelfPassPerm, "Edit Self Password Permission?:", layout);

}

void EditCommitteeView::setUpPermButton(QRadioButton *perm, const char *mess, FormLayoutPtr *layout)
{
    QButtonGroup *permGroup(new QButtonGroup);
    QRadioButton *noPerm(new QRadioButton("No"));
    perm = new QRadioButton("Yes");
    permGroup->addButton(perm);
    permGroup->addButton(noPerm);
    *layout << mess | perm | noPerm;
}
