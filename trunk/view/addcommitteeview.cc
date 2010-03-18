#include "addcommitteeview.h"

AddCommitteeView::AddCommitteeView(QWidget *parent) : QDialog(parent) {
    FormLayoutPtr layout(this);

    //layout
    committeeName = layout << "Committee Name: " |= new QLineEdit;
    selectChair = layout << "Select a Chair" |= new ModelListWidget<MemberModel>;
    selectSecretary = layout << "Select a Secretary" |= new ModelListWidget<MemberModel>;

    //Add / cancel buttons
    QPushButton *addButton = new QPushButton("Add Committee");
    QPushButton *cancelButton = new QPushButton("Cancel");

    layout << addButton | cancelButton;

    //misc
    setModal(true);
    setWindowTitle("Add Committee");

    MemberModel::iterator_range members(MemberModel::findAll("committee_id=0"));
    selectChair->fill(members);
    selectSecretary->fill(members);

    //Connect slots/signals
    connect(addButton, SIGNAL(clicked()), this, SLOT(addCommittee()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelCommittee()));

}

AddCommitteeView::~AddCommitteeView(){}

void AddCommitteeView::addCommittee()
{
    int chairID;
    int secID;

    if(!committeeName->isModified()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a Committee name"
        );
        return;
    }
    if(selectChair->getModel() == 0)
    {
        chairID = 0;
    }
    else
    {
        chairID = selectChair->getModel()->id;
    }

    if(selectSecretary->getModel() == 0)
    {
        secID = 0;
    }
    else
    {
        secID = selectSecretary->getModel()->id;
    }

    CommitteeModel::create(
        committeeName->text(),
        true,
        0, 0, chairID,
        secID
    );
    done(QDialog::Accepted);
}

void AddCommitteeView::cancelCommittee()
{
    done(QDialog::Rejected);
}


