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

#include "view/homeview.h"

class EditMemberView : public QDialog
{
public:
    EditMemberView(MemberModel *selectedmember, QWidget *parent=0);
    ~EditMemberView(void);
private:
    QLineEdit *first_name;
    QLineEdit *last_name;
    QLineEdit *phone_number;
    //QLineEdit *unitno;
//    QComboBox *unitno;
    //QLineEdit *address;
    QComboBox *address;
    QLineEdit *password;
    QDateEdit *date_moved_in;
    QLineEdit *user_name;
    QRadioButton *share_phone_number;
    QRadioButton *assign_committee;
    MemberModel *member;

    ModelListWidget<CommitteeModel> *committee;
    void dataInit(void);

public slots:
    void saveChange(void);
    void cancelEdit(void);
    void resetChange(void);

};

#endif // EDITMEMBERVIEW_H
