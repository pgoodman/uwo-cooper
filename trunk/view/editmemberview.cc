
#include "editmemberview.h"

/**
 * Construct the view.
 */
EditMemberView::EditMemberView(MemberModel *selectedmember, QWidget *parent)
 : AddMemberView(0, parent) {
    member = selectedmember;

    FormLayoutPtr layout(this);
    buildForm(layout);
    AddMemberView::finishForm(layout);
    initForm();

    save_button->setText("Update Member");
    setWindowTitle("Edit Member Information");
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
    layout [2] << "If a field is disabled then either you are not allowed "
                  "to edit the field \nor it can only be edited elsewhere.";
    layout [2] << "If a field is missing then that information is private "
                  "or must be edited elsewhere.";
    layout << ""; // empty row
    AddMemberView::buildForm(layout);
    balance_due = layout << "Balance Owing: " |= new QLineEdit(this);
}

/**
 * Initialize all of the fields. This deals with all of the scary corners of
 * how the permissions interact.
 */
void EditMemberView::initForm(void) {
    share_phone_number->setChecked(member->isTelephoneShared());
    date_moved_in->setDate(member->getMoveInTime().date());
    first_name->setText(member->getFirstName());
    last_name->setText(member->getLastName());
    phone_number->setText(member->getTelephoneNum());
    address->setText(member->getAddress());
    user_name->setText(member->getLoginName());
    password->setText(member->getPassword());
    balance_due->setText(QVariant(member->getMoneyOwed()).toString());

    if(!checkPerm(EDIT_MEMBER_INFO)) {
        share_phone_number->setDisabled(true);
        dont_share_phone->setDisabled(true);
        date_moved_in->setReadOnly(true);
        first_name->setReadOnly(true);
        last_name->setReadOnly(true);
        phone_number->setReadOnly(true);
        address->setReadOnly(true);
        user_name->setReadOnly(true);
        balance_due->setReadOnly(true);

        // don't divulge this info!
        //user_name->hide();
        //password->hide();

        // interesting interactions with the other permissions!
        // this control is done through the controlmemberview by whether enabling the edit button
        // also, active_user and member are different class instances.
        // the comparison here is not effective. Use id to compare
        /*
            if((member != active_user && !checkPerm(VIEW_OTHER_INFO))
            || !checkPerm(VIEW_SELF_INFO)) {
                share_phone_number->hide();
                date_moved_in->hide();
                address->hide();

                if(!checkPerm(PRINT_PUBLIC_LIST)) {
                    first_name->hide();
                    last_name->hide();
                    unit->hide();
                }

                if(!checkPerm(PRINT_COMMITTEE_LIST)) {
                    committee->hide();
                }

                if(!checkPerm(PRINT_PRIVATE_LIST)) {
                    phone_number->hide();
                }
            }*/
    }

    password->setDisabled(false);


    if(0 == member->findCommittee()) {
        if((!member->wasAssignedCommittee() && checkPerm(INIT_MEMBER_COMMITTEE))
        || checkPerm(EDIT_MEMBER_COMMITTEE)) {
            committee->show();
            committee->selectFirst();
        } else {
            committee->setDisabled(true);
            assign_committee->setDisabled(true);
            dont_assign_committee->setDisabled(true);
        }

    // don't allow the committee to be changed, this is done elsewhere
    // under moving a member from one committee to another
    } else {
        committee->clear();
        committee->addModel(member->findCommittee());
        committee->selectFirst();
        committee->setDisabled(true);
        assign_committee->setDisabled(true);
        dont_assign_committee->setDisabled(true);
        //committee->hide();
        //assign_committee->hide();
        //dont_assign_committee->hide();
    }

    // change the unit list somewhat, the unit cannot be edited here. That is,
    // it must be changed through an internal move once set.
    unit->clear();
    if(0 != member->findUnit()) {
        unit->addModel(member->findUnit());
        unit->selectFirst();
        unit->setDisabled(true);
        //unit->hide();
        unit_is_empty->setDisabled(true);
        unit_not_empty->setDisabled(true);
    }
}

/**
 * Update the member.
 */
void EditMemberView::accept() {

    //valid data and change exists
    if(first_name->text().isEmpty()) {
        QMessageBox::information(
            this, "Invalid Field",
            "Please enter a given name."
        );
        return;
    }
    if(last_name->text().isEmpty()) {
        QMessageBox::information(
            this, "Invalid Field",
            "Please enter a surname (family name / last name)."
        );
        return;
    }
    if(!Validator::isValidPhoneNo(phone_number->text())) {
        QMessageBox::information(
            this, "Invalid Field",
            "Please enter a valid phone number."
        );
        return;
    }
    if(user_name->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a user login name."
        );
        return;
    }
    if(password->text().isEmpty()) {
        QMessageBox::information(
            this, "Empty Field",
            "Please enter a password."
        );
        return;
    }
    if(!Validator::isValidDigit(balance_due->text())) {
        QMessageBox::information(
            this, "Invalid Field",
            "Please enter a valid owning number."
        );
        return;
    }
    member->setFirstName(first_name->text());
    member->setLastName(last_name->text());
    member->setTelephoneNumber(phone_number->text());
    member->setLoginName(user_name->text());
    member->setPassword(password->text());
    member->setAddress(address->text());
    member->setSharedTelephone(share_phone_number->isChecked());
    member->setMoveInTime(date_moved_in->dateTime());
    member->setMoneyOwed(QVariant(balance_due->text()).toFloat());

    // assign the committee
    if(assign_committee->isChecked()
    && committee->isEnabled()
    && 0 != committee->getSelectedModel()) {

        member->setCommittee(committee->getSelectedModel());
    }

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
