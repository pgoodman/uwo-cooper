
#include "editmemberview.h"

#include "editmemberview.h"

EditMemberView::EditMemberView(MemberModel *selectedmember, QWidget *parent)
 : AddMemberView(parent) {

    member = selectedmember;
    setWindowTitle("Update Member Information");
    initForm();
}

/**
 * Check to see if the active user has a permission set.
 */
bool EditMemberView::checkPerm(PermissionModelSet perm) {
    return active_user->hasPermission(perm);
}

/**
 * Build the rest of the form that is not part of the add member form.
 */
void EditMemberView::buildForm(FormLayoutPtr &layout) {
    AddMemberView::buildForm(layout);
}

/**
 * Initialize all of the fields.
 */
void EditMemberView::initForm(void) {
    committee->selectModel(member->findCommittee());
    share_phone_number->setChecked(member->isTelephoneShared());
    date_moved_in->setDate(member->getMoveInTime().date());
    first_name->setText(member->getFirstName());
    last_name->setText(member->getLastName());
    phone_number->setText(member->getTelephoneNum());
    address->setText(member->getAddress());
    user_name->setText(member->getLoginName());
    password->setText(member->getPassword());

    // don't allow the committee to be changed, this is done elsewhere
    // under moving a member from one committee to another
    if(0 == member->findCommittee()) {
        if((!member->wasAssignedCommittee() && checkPerm(INIT_MEMBER_COMMITTEE))
        || checkPerm(EDIT_MEMBER_COMMITTEE)) {
            committee->selectFirst();
        } else {
            committee->clear();
            committee->addModel(member->findCommittee());
            committee->setDisabled(true);
            assign_committee->setDisabled(true);
            dont_assign_committee->setDisabled(true);
        }
    }

}

/**
 * Update the member.
 */
void EditMemberView::accept() {

    //valid data and change exists
    member->setFirstName(first_name->text());
    member->setLastName(last_name->text());
    member->setTelephoneNumber(phone_number->text());
    member->setLoginName(user_name->text());
    member->setPassword(password->text());
    member->setAddress(address->text());
    member->setSharedTelephone(share_phone_number->isChecked());

    member->setMoveInTime(date_moved_in->dateTime());

    member->save();

    QDialog::accept();
}

/**
 * Check the username.
 */
bool EditMemberView::checkUserName(QString name) {

    // note: check for same name follows as the name might be uninitialized
    //       iff the member is incomplete (i.e. added by data load).
    return AddMemberView::checkUserName(name)
        || (name == member->getLoginName());
}

/**
 * Check the input data.
 */
bool EditMemberView::checkForm(void) {
    if(!AddMemberView::checkForm()) {
        return false;
    }



    return true;
}
