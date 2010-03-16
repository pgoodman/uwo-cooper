#ifndef EDITMEMBERVIEW_H
#define EDITMEMBERVIEW_H

#include <QDialog>
#include <QWidget>
#include <QList>
#include <QLineEdit>
#include <QVariant>

#include "model/membermodel.h"
#include "model/dependantmodel.h"

#include "view/addmemberview.h"

class EditMemberView : public AddMemberView
{
    Q_OBJECT

protected:
    MemberModel *member;

    QLineEdit *balance_due;

    void initForm(void);
    void buildForm(FormLayoutPtr &layout);
    void finishForm(FormLayoutPtr &layout);

    virtual bool checkForm(void);
    virtual bool checkUserName(QString name);
    virtual bool checkPerm(PermissionModelSet perm);

public:
    EditMemberView(MemberModel *memberToEdit, QWidget *parent=0);

public slots:
    virtual void accept(void);
};

#endif // EDITMEMBERVIEW_H
