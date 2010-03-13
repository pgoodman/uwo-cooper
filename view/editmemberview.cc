#include "editmemberview.h"

EditMemberView::EditMemberView(MemberModel *selectedmember, QWidget *parent) : QDialog(parent) {
    FormLayoutPtr layout(this);
    //get the currentmember
    member = selectedmember;

    // make the yes/no buttons for the phone number
    QButtonGroup *share_phone_group(new QButtonGroup);
    QRadioButton *dont_share_phone(new QRadioButton("No"));
    share_phone_number = new QRadioButton("Yes");
    share_phone_group->addButton(share_phone_number);
    share_phone_group->addButton(dont_share_phone);


    // make yes/no buttons for assigning a committee
    QButtonGroup *assign_committee_group(new QButtonGroup);
    assign_committee = new QRadioButton("Yes");
    QRadioButton *dont_assign_committee(new QRadioButton("No"));
    assign_committee_group->addButton(assign_committee);
    assign_committee_group->addButton(dont_assign_committee);


    // make the layout of the form
    first_name = layout << "First Name: " |= new QLineEdit;
    last_name = layout << "Last Name: " |= new QLineEdit;
    phone_number = layout << "Telephone Number: " |= new QLineEdit;

    layout << "Share Telephone Number?: " | share_phone_number;
    layout << "" | dont_share_phone;

    //unit address and unit no.
    address =  layout << "Address: " |= new QComboBox;
//    unitno = layout << "Unit No.: " |= new QComboBox;

    //move in date
    date_moved_in = layout << "Date Moved In: " |= new QDateEdit;

    layout << "Set Committee?: " | assign_committee;
    layout << "" | dont_assign_committee;
    committee = layout << "Committee: " |= new ModelListWidget<CommitteeModel>;

    user_name = layout << "Login Name: " |= new QLineEdit;
    password = layout << "Password: " |= new QLineEdit;

    // make and add in the buttons
    QPushButton *save(new QPushButton("Save Changes"));
    QPushButton *reset(new QPushButton("Reset Changes"));
    QPushButton *cancel(new QPushButton("Cancel"));
    layout << save | reset | cancel;

    // misc
    date_moved_in->setCalendarPopup(true);
    committee->fill(&CommitteeModel::findAll);
    setModal(true);
    setWindowTitle("Update Member Information");

    // signals / slots
    connect(
        assign_committee, SIGNAL(toggled(bool)),
        committee, SLOT(setEnabled(bool))
    );


    connect(save, SIGNAL(clicked()), this, SLOT(addMember()));
    connect(reset, SIGNAL(clicked()), this, SLOT(resetChange()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelAdd()));

    dataInit();
}

/**
 * Destructor.
 */
EditMemberView::~EditMemberView(void) { }

void EditMemberView::dataInit(){

    //sharing phone?
    if(member->isTelephoneShared()) {
        share_phone_number->setChecked(true);
    }else{
        share_phone_number->setChecked(false);
    }

    //Check permission
    //if(member->hasPermission())

    //move in date
    date_moved_in->setDate(member->getMoveInTime().date());

    //committee
    if(member->getCommitteeId()!=0){
        assign_committee->setChecked(true);
        CommitteeModel * cm = member->getCommittee();

        QString cname = cm->toString();
        QList<QListWidgetItem *> ql = committee->findItems(cname,Qt::MatchExactly);
        if(ql.isEmpty()){
            QMessageBox::information(
                this, "Data Consistency Error",
                "Slected member's committee does not exist in the committee list"
            );
        }else{
            committee->setCurrentItem(ql.first());
        }
    }else{
        assign_committee->setChecked(false);
    }

    //check permission

    //first name and last name
    first_name->setText(member->getFirstName());
    last_name->setText(member->getLastName());

    //phone number
    phone_number->setText(member->getTelephoneNum());

    //login name and password
    user_name->setText(member->getLoginName());
    password->setText(member->getPassword());

    //unit address. load all info into combobox
    QStringList *qladdr = UnitModel::findAllAddress();
    address->addItems(*qladdr);
    delete qladdr;

    /*QStringList *qlno = UnitModel::findAllUnitNoByAddress("");
    unitno->addItems(*qlno);
    delete qlno;*/

    //set current item
    int addrid = address->findText(member->getAddress());
    if (addrid!=-1){
        address->setCurrentIndex(addrid);
    }

//    int numberid = unitno->findText(member->getUnitNo());
//    if(numberid!=-1){
//        unitno->setCurrentIndex(numberid);
//    }

}

void EditMemberView::resetChange(void){

}

void EditMemberView::cancelEdit(void) {
    done(QDialog::Rejected);
}
