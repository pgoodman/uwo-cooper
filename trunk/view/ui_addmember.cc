#include "ui_addmember.h"


Ui_AddMember::Ui_AddMember(QWidget *parent) : QDialog(parent)
{
    layout = new QGridLayout;
    layout->setObjectName(QString::fromUtf8("layout"));

    layout = new QGridLayout();
    layout->setObjectName(QString::fromUtf8("layout"));
    LastNameLabel = new QLabel();
    LastNameLabel->setObjectName(QString::fromUtf8("LastNameLabel"));

    layout->addWidget(LastNameLabel, 0, 0, 1, 1);

    LastNameEdit = new QLineEdit();
    LastNameEdit->setObjectName(QString::fromUtf8("LastNameEdit"));
    LastNameEdit->setEnabled(true);

    layout->addWidget(LastNameEdit, 0, 2, 1, 4);

    GivenNameLabel = new QLabel();
    GivenNameLabel->setObjectName(QString::fromUtf8("GivenNameLabel"));

    layout->addWidget(GivenNameLabel, 1, 0, 1, 1);

    GivenNameEdit = new QLineEdit();
    GivenNameEdit->setObjectName(QString::fromUtf8("GivenNameEdit"));
    GivenNameEdit->setEnabled(true);

    layout->addWidget(GivenNameEdit, 1, 2, 1, 4);

    NumberLabel = new QLabel();
    NumberLabel->setObjectName(QString::fromUtf8("NumberLabel"));

    layout->addWidget(NumberLabel, 2, 0, 1, 2);

    NumberEdit = new QLineEdit();
    NumberEdit->setObjectName(QString::fromUtf8("NumberEdit"));
    NumberEdit->setEnabled(true);

    layout->addWidget(NumberEdit, 2, 2, 1, 4);

    UnitLabel = new QLabel();
    UnitLabel->setObjectName(QString::fromUtf8("UnitLabel"));

    layout->addWidget(UnitLabel, 3, 0, 1, 1);

    UnitEdit = new QLineEdit();
    UnitEdit->setObjectName(QString::fromUtf8("UnitEdit"));
    UnitEdit->setEnabled(true);

    layout->addWidget(UnitEdit, 3, 2, 1, 4);

    CommitteeLabel = new QLabel();
    CommitteeLabel->setObjectName(QString::fromUtf8("CommitteeLabel"));

    layout->addWidget(CommitteeLabel, 4, 0, 1, 1);

    CommitteeNoButton = new QRadioButton();
    buttonGroup_3 = new QButtonGroup();
    buttonGroup_3->setObjectName(QString::fromUtf8("buttonGroup_3"));
    buttonGroup_3->addButton(CommitteeNoButton);
    CommitteeNoButton->setObjectName(QString::fromUtf8("CommitteeNoButton"));
    CommitteeNoButton->setChecked(true);

    layout->addWidget(CommitteeNoButton, 4, 1, 1, 1);

    CommitteeYesButton = new QRadioButton();
    buttonGroup_3->addButton(CommitteeYesButton);
    CommitteeYesButton->setObjectName(QString::fromUtf8("CommitteeYesButton"));

    layout->addWidget(CommitteeYesButton, 4, 2, 1, 1);

    committee_list = new ModelList<Committee>;
    committee_list->setEnabled(false);
    committee_list->fill(&Committee::findAll);
    layout->addWidget(committee_list, 4, 3, 1, 3);

    UserIDLabel = new QLabel();
    UserIDLabel->setObjectName(QString::fromUtf8("UserIDLabel"));

    layout->addWidget(UserIDLabel, 5, 0, 1, 1);

    UserIDEdit = new QLineEdit();
    UserIDEdit->setObjectName(QString::fromUtf8("UserIDEdit"));
    UserIDEdit->setEnabled(true);

    layout->addWidget(UserIDEdit, 5, 2, 1, 4);

    PasswordLabel = new QLabel();
    PasswordLabel->setObjectName(QString::fromUtf8("PasswordLabel"));

    layout->addWidget(PasswordLabel, 6, 0, 1, 1);

    PasswordEdit = new QLineEdit();
    PasswordEdit->setObjectName(QString::fromUtf8("PasswordEdit"));

    layout->addWidget(PasswordEdit, 6, 2, 1, 4);

    label = new QLabel();
    label->setObjectName(QString::fromUtf8("label"));

    layout->addWidget(label, 7, 0, 1, 1);

    /*lineEdit = new QLineEdit();
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setEnabled(true);

    layout->addWidget(lineEdit, 7, 2, 1, 2);*/

    dateEdit = new QDateEdit();
    dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
    dateEdit->setCalendarPopup(true);

    layout->addWidget(dateEdit, 7, 2, 1, 2);

    InArrearsLabel = new QLabel();
    InArrearsLabel->setObjectName(QString::fromUtf8("InArrearsLabel"));

    layout->addWidget(InArrearsLabel, 8, 0, 1, 1);

    ArrearsNoButton = new QRadioButton();
    buttonGroup_2 = new QButtonGroup();
    buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
    buttonGroup_2->addButton(ArrearsNoButton);
    ArrearsNoButton->setObjectName(QString::fromUtf8("ArrearsNoButton"));
    ArrearsNoButton->setChecked(true);

    layout->addWidget(ArrearsNoButton, 8, 2, 1, 1);

    ArrearYesButton = new QRadioButton();
    buttonGroup_2->addButton(ArrearYesButton);
    ArrearYesButton->setObjectName(QString::fromUtf8("ArrearYesButton"));

    layout->addWidget(ArrearYesButton, 8, 4, 1, 1);

    ArrearsAmountEdit = new QLineEdit();
    ArrearsAmountEdit->setObjectName(QString::fromUtf8("ArrearsAmountEdit"));
    ArrearsAmountEdit->setEnabled(false);
    ArrearsAmountEdit->setFrame(true);
    ArrearsAmountEdit->setDragEnabled(false);
    ArrearsAmountEdit->setReadOnly(false);

    layout->addWidget(ArrearsAmountEdit, 8, 5, 1, 1);

    PrivateNoLabel = new QLabel();
    PrivateNoLabel->setObjectName(QString::fromUtf8("PrivateNoLabel"));

    layout->addWidget(PrivateNoLabel, 9, 0, 1, 1);

    PrivateNoButton = new QRadioButton();
    buttonGroup = new QButtonGroup();
    buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
    buttonGroup->addButton(PrivateNoButton);
    PrivateNoButton->setObjectName(QString::fromUtf8("PrivateNoButton"));
    PrivateNoButton->setChecked(true);

    layout->addWidget(PrivateNoButton, 9, 2, 1, 1);

    PrivateYesButton = new QRadioButton();
    buttonGroup->addButton(PrivateYesButton);
    PrivateYesButton->setObjectName(QString::fromUtf8("PrivateYesButton"));

    layout->addWidget(PrivateYesButton, 9, 4, 1, 1);

    label_2 = new QLabel();
    label_2->setObjectName(QString::fromUtf8("label_2"));

    layout->addWidget(label_2, 10, 0, 1, 4);

    under21NoButton = new QRadioButton();
    under21NoButton->setObjectName(QString::fromUtf8("under21NoButton"));
    under21NoButton->setChecked(true);

    layout->addWidget(under21NoButton, 10, 4, 1, 1);

    Under21YesButton = new QRadioButton();
    Under21YesButton->setObjectName(QString::fromUtf8("Under21YesButton"));

    layout->addWidget(Under21YesButton, 10, 5, 1, 1);

    Under21List = new QTextEdit();
    Under21List->setObjectName(QString::fromUtf8("Under21List"));
    Under21List->setEnabled(false);

    layout->addWidget(Under21List, 10, 6, 1, 1);

    addNewButton = new QPushButton();
    addNewButton->setObjectName(QString::fromUtf8("addMember"));
    connect(addNewButton, SIGNAL(clicked()), this, SLOT(addMember()));
 //   connect(addNewButton, SIGNAL(clicked()), this, SLOT(accept()));

    layout->addWidget(addNewButton, 11, 2, 1, 3);

    cancelButton = new QPushButton();
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    layout->addWidget(cancelButton, 11, 5, 1, 1);

    setLayout(layout);
    setWindowTitle(tr("Add Member"));

    if(!User::canDo(EDIT_MEMBER_STATUS)){
        LastNameEdit->setReadOnly(true);
        GivenNameEdit->setReadOnly(true);
        UnitEdit->setReadOnly(true);
        CommitteeNoButton->setDisabled(true);
        CommitteeYesButton->setDisabled(true);
        committee_list->setDisabled(true);
        UserIDEdit->setReadOnly(true);
        NumberEdit->setReadOnly(true);
        dateEdit->setReadOnly(true);
        ArrearsNoButton->setDisabled(true);
        ArrearYesButton->setDisabled(true);
        ArrearsAmountEdit->setReadOnly(true);
        Under21YesButton->setDisabled(true);
        under21NoButton->setDisabled(true);
        Under21List->setReadOnly(true);
        PrivateYesButton->setDisabled(true);
        PrivateNoButton->setDisabled(true);
    }

    retranslateUi();
    QObject::connect(Under21YesButton, SIGNAL(toggled(bool)), Under21List, SLOT(setEnabled(bool)));
    QObject::connect(ArrearYesButton, SIGNAL(toggled(bool)), ArrearsAmountEdit, SLOT(setEnabled(bool)));
    QObject::connect(CommitteeYesButton, SIGNAL(toggled(bool)), committee_list, SLOT(setEnabled(bool)));

    setModal(true);

//    QMetaObject::connectSlotsByName();
} // setupUi

void Ui_AddMember::retranslateUi()
{

   // ->setWindowTitle(QApplication::translate("", "", 0, QApplication::UnicodeUTF8));
    UserIDLabel->setText(QApplication::translate("", "Login Name:", 0, QApplication::UnicodeUTF8));
    LastNameLabel->setText(QApplication::translate("", "Last Name:", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("", "Move-in Date: mm/dd/yyyy", 0, QApplication::UnicodeUTF8));
    ArrearYesButton->setText(QApplication::translate("", "Yes:", 0, QApplication::UnicodeUTF8));
    LastNameEdit->setText(QString());
    CommitteeLabel->setText(QApplication::translate("", "In Committee?:", 0, QApplication::UnicodeUTF8));
    PrivateYesButton->setText(QApplication::translate("", "Yes", 0, QApplication::UnicodeUTF8));
    InArrearsLabel->setText(QApplication::translate("", "In Arrears?", 0, QApplication::UnicodeUTF8));
    PasswordLabel->setText(QApplication::translate("", "Password:", 0, QApplication::UnicodeUTF8));
    addNewButton->setText(QApplication::translate("addMember", "Add New Member", 0, QApplication::UnicodeUTF8));
    GivenNameLabel->setText(QApplication::translate("", "Given Name(s):", 0, QApplication::UnicodeUTF8));
    NumberLabel->setText(QApplication::translate("", "Telephone Number:", 0, QApplication::UnicodeUTF8));
    UnitLabel->setText(QApplication::translate("", "Unit Number:", 0, QApplication::UnicodeUTF8));
    ArrearsNoButton->setText(QApplication::translate("", "No", 0, QApplication::UnicodeUTF8));
    PrivateNoButton->setText(QApplication::translate("", "No", 0, QApplication::UnicodeUTF8));
    PrivateNoLabel->setText(QApplication::translate("", "Private Number?", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("", "Cancel", 0, QApplication::UnicodeUTF8));
    CommitteeNoButton->setText(QApplication::translate("", "No", 0, QApplication::UnicodeUTF8));
    CommitteeYesButton->setText(QApplication::translate("", "Yes: ", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("", "Anyone Under 21 Living with Member?", 0, QApplication::UnicodeUTF8));
    under21NoButton->setText(QApplication::translate("", "No", 0, QApplication::UnicodeUTF8));
    Under21YesButton->setText(QApplication::translate("", "Yes (Please enter name and age):", 0, QApplication::UnicodeUTF8));
} // retranslateUi

void Ui_AddMember::addMember(void) {

    QString lastname = LastNameEdit->text();
    QString name = GivenNameEdit->text();
    QString telephone = NumberEdit->text();
    QString unit = UnitEdit->text();
    //QString committee = CommitteeEdit->text();
    QString userid = UserIDEdit->text();
    QString password = PasswordEdit->text();
    //QString date = lineEdit->text();
    QDate date=dateEdit->date();

    if(lastname.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a surname (family name)."));
        return;
    }

    if(name.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a given name (first name)."));
        return;
    }

    if(telephone.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a phone number."));
        return;
    }

    if(unit.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a unit number."));
        return;
    }

    if(CommitteeYesButton->isDown() && 0 == committee_list->getModel())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a committee."));
        return;
    }

    if(userid.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a login name."));
        return;
    } else if(User::nameExists(userid)) {
        QMessageBox::information(this, tr("Bad Field"), tr(
            "That login name is already in use. Please choose "
            "another one."
        ));
        return;
    }

    if(password.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a password."));
        return;
    }

    if(date.isNull())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a valid move-in date."));
        return;
    }

    cout << "getting committee id." << endl;

    int committee_id(0);
    if(CommitteeYesButton->isChecked()) {
        Committee *comm(committee_list->getModel());
        committee_id = (0 == comm) ? 0 : comm->getId();
    }

    cout << "adding member." << endl;


    Member::create(
        name, lastname, telephone, PrivateYesButton->isDown(),
        userid, password, QDateTime(date).toTime_t(), committee_id
    );

    cout << "done." << endl;

    done(QDialog::Accepted);
}

void Ui_AddMember::setSelectedMember(Member* selMem){
    selectedMember=selMem;
}

void Ui_AddMember::saveChanges(){
    //the sender() should be editMemberDialog.
    //Check sender's class name is safer
    bool isdirty=false;

    QString lastname = LastNameEdit->text();
    QString name = GivenNameEdit->text();
    QString telephone = NumberEdit->text();
    QString unit = UnitEdit->text();
    QString userid = UserIDEdit->text();
    QString password = PasswordEdit->text();
    //QString date = lineEdit->text();
    QDate qdate = dateEdit->date();

    //validate fields for mandatory and format
    if(lastname.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a surname (family name)."));
        return;
    }

    if(name.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a given name (first name)."));
        return;
    }

    if(telephone.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a phone number."));
        return;
    }

    if(unit.isEmpty()||!unit.toInt())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a valid unit number."));
        return;
    }

    if(CommitteeYesButton->isChecked() && 0 == committee_list->getModel())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a committee."));
        return;
    }

    if(userid.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a login name."));
        return;
    } else if(User::nameExists(userid)&&userid!=selectedMember->getLastName()) {
        QMessageBox::information(this, tr("Bad Field"), tr(
            "That login name is already in use. Please choose "
            "another one."
        ));
        return;
    }

    if(password.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a password."));
        return;
    }

    if(qdate.isNull())
    {
        QMessageBox::information(this, tr("Empty Field"),
                     tr("Please enter a valid move-in date."));
        return;
    }

    if(LastNameEdit->isModified()){
        selectedMember->setLastName(lastname);
        isdirty=true;
    }
    if(GivenNameEdit->isModified()){
        selectedMember->setFirstName(name);
        isdirty=true;
    }

    if(NumberEdit->isModified()){
        selectedMember->setTelephoneNumber(telephone);
        isdirty=true;
    }
    if(UnitEdit->isModified()){
        selectedMember->setUnit(unit.toInt());
        isdirty=true;
    }
    if(UserIDEdit->isModified()){
        selectedMember->setLoginName(userid);
        isdirty=true;
    }
    if(PasswordEdit->isModified()){
        selectedMember->setPassword(password);
        isdirty=true;
    }
    /*if(lineEdit->isModified()){
        QDate _t;
        _t.fromString(date,"MM'/'dd'/'yyyy");
        QDateTime _dt(_t);
        selectedMember->setMoveInTime(_dt);
    }*/

    time_t _tt=selectedMember->getMoveInTime();
    //_mit->fromTime_t(_tt);
    if(dateEdit->date()!= QDateTime::fromTime_t(_tt).date()){
        QDateTime *_mit = new QDateTime(dateEdit->date());
        selectedMember->setMoveInTime(*_mit);
        delete _mit;
    }


    if (isdirty) {
        selectedMember->save();
    }

    done(QDialog::Accepted);
}

//reset used made changes.
void Ui_AddMember::resetChanges(){
    fillEditForm();
}

void Ui_AddMember::fillEditForm(){
    if(!selectedMember==0){
        LastNameEdit->setText(selectedMember->getLastName());
        GivenNameEdit->setText(selectedMember->getFirstName());
        double _m=selectedMember->getMoneyOwed();
        if(_m!=0) {
            QString _mStr;
            ArrearYesButton->setChecked(true);
            ArrearsAmountEdit->setText(_mStr.setNum(_m));
        }
        else {
            ArrearYesButton->setChecked(false);
            ArrearsAmountEdit->setText("");
        }
        PrivateNoButton->setChecked(selectedMember->isTelephoneShared());
        PasswordEdit->setText(selectedMember->getPassword());
        NumberEdit->setText(selectedMember->getTelephoneNum());
        time_t _t = selectedMember->getMoveInTime();

        QDateTime _qdt;
        _qdt = QDateTime::fromTime_t(_t);
        dateEdit->setDate(_qdt.date());
        //QString _qt;
        // time(&_t);
        //_qt.fromStdString(ctime(&_t));
        //lineEdit->setText(_qt);

        UserIDEdit->setText(selectedMember->getLoginName());
        if(!selectedMember->getCommittee()==0){
            CommitteeYesButton->setChecked(true);
            //assume committee name is unique. otherwise, have to go through all matched items
            int _id = selectedMember->getCommitteeID();
            Committee *_committee = Committee::load(_id);
            QListWidgetItem * _qli =committee_list->findItems(_committee->toString(),Qt::MatchExactly)[0];
            committee_list->setCurrentItem(_qli);
            //_qli->setSelected(true);

            //_qli->setBackgroundColor(Qt::red);
        }
        else
            CommitteeYesButton->setChecked(false);

    }
}
