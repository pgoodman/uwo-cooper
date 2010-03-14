#ifndef EDITMEMBERVIEW_H
#define EDITMEMBERVIEW_H

#include <QDialog>
#include <QWidget>

#include "model/usermodel.h"
#include "model/membermodel.h"

#include "view/addmemberview.h"

class EditMemberView : public AddMemberView
{
    Q_OBJECT

protected:
    MemberModel *member;

    virtual void initForm(void);
    virtual void buildForm(FormLayoutPtr &layout);
    virtual bool checkForm(void);
    virtual bool checkUserName(QString name);
    virtual bool checkPerm(PermissionModelSet perm);

public:
    EditMemberView(MemberModel *memberToEdit, QWidget *parent=0);

public slots:
    virtual void accept(void);
};

#endif // EDITMEMBERVIEW_H
