#ifndef MODEL_USER_H
#define MODEL_USER_H

#include <QString>
#include <QSqlQuery>

#include "lib/database.h"
#include "model/permissionmodel.h"

class UserModel {
public:

    virtual QString getUserName() = 0;
    virtual bool hasPermission(const PermissionModel p) = 0;

    virtual QString getPassword(void);
    virtual void setPassword(QString);

    bool hasPassword(QString &pass);

    virtual ~UserModel();

    static void setActive(UserModel *);
    static bool canDo(PermissionModel); // can't re-declare hasPermission :/
    static bool nameExists(QString userName);

protected:
    UserModel(const bool isCoordinator, QString &pwd);
    
    const bool is_coordinator;
    QString password;

private:
    static UserModel *active;
};

#endif // MODEL_USER_H
