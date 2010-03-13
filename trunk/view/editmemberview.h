#ifndef EDITMEMBERVIEW_H
#define EDITMEMBERVIEW_H

#include <ctime>

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QMessageBox>

#include "lib/gui/modellistwidget.h"
#include "lib/gui/formlayoutptr.h"

#include "model/membermodel.h"
#include "model/committeemodel.h"
#include "model/unitmodel.h"
#include "model/usermodel.h"
#include "model/permissionmodel.h"

#include "view/homeview.h"

class EditMemberView : public QDialog
{
    Q_OBJECT
public:
    EditMemberView(MemberModel *selectedmember, QWidget *parent=0);
    ~EditMemberView(void);
private:
    QLineEdit *first_name;
    QLineEdit *last_name;
    QLineEdit *phone_number;
    QComboBox *address;
    QLineEdit *password;
    QDateEdit *date_moved_in;
    QLineEdit *user_name;
    QRadioButton *share_phone_number;
    QRadioButton *dont_share_phone;
    QRadioButton *assign_committee;
    QRadioButton *dont_assign_committee;
    MemberModel *member;

    ModelListWidget<CommitteeModel> *committee;
    void dataInit(void);
    bool dataCheck(void);
    void permissionFilter(void);

public slots:
    void saveChange(void);
    void cancelEdit(void);
    void resetChange(void);

};

#endif // EDITMEMBERVIEW_H
