
#include "editmemberview.h"

#include "editmemberview.h"

EditMemberView::EditMemberView(MemberModel *selectedmember, QWidget *parent)
 : QDialog(parent) {

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
    address =  layout << "Address: " |= new QLineEdit;

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
    connect(save, SIGNAL(clicked()), this, SLOT(saveChange()));
    connect(reset, SIGNAL(clicked()), this, SLOT(resetChange()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    dataInit();
}

/**
 * Destructor.
 */
EditMemberView::~EditMemberView() {

}

void EditMemberView::dataInit(){
    committee->selectModel(member->findCommittee());
    share_phone_number->setChecked(member->isTelephoneShared());
    date_moved_in->setDate(member->getMoveInTime().date());
    first_name->setText(member->getFirstName());
    last_name->setText(member->getLastName());
    phone_number->setText(member->getTelephoneNum());
    address->setText(member->getAddress());
    user_name->setText(member->getLoginName());
    password->setText(member->getPassword());
}
void EditMemberView::permissionFilter(){

    if(active_user->hasPermission(EDIT_SELF_PASS)){

    }

}

void EditMemberView::saveChange(){
    //invalid data or no change
    if(!dataCheck()){
        return;
    }

    //valid data and change exists
    member->setFirstName(first_name->text());
    member->setLastName(last_name->text());
    member->setTelephoneNumber(phone_number->text());
    member->setLoginName(user_name->text());
    member->setPassword(password->text());
    member->setAddress(address->text());
    member->setSharedTelephone(share_phone_number->isChecked());

    CommitteeModel *selected_committee();

    if(assign_committee->isChecked()) {
       member->setCommittee(committee->getModel());
    } else {
       member->setCommittee(0);
    }

    QDateTime *mvtime = new QDateTime(date_moved_in->date());
    member->setMoveInTime(*mvtime);

    member->save();

    emit accept();
}

void EditMemberView::resetChange(){
    dataInit();
}

/**
 * Check the input data.
 */
bool EditMemberView::dataCheck(){
    if(first_name->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a given name"
        );
        return false;
    }

    if(last_name->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a surname"
        );
        return false;
    }

    if(phone_number->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a telephone number."
        );
        return false;
    }

    if(assign_committee->isChecked() && 0 == committee->getModel()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please select a committee."
        );
        return false;
    }

    if(user_name->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter an log in name."
        );
        return false;
    }

    if(password->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter an password."
        );
        return false;
    }

    return true;
}
