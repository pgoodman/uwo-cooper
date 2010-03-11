
#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <QString>

#include <QSqlQuery>
#include <QVariant>

#include "conf.h"
#include "database.h"

#include "model/usermodel.h"
#include "model/permissionmodel.h"

using namespace std;

class CoordinatorModel : public UserModel {

public:
    static bool exists(void);
    static UserModel *create(QString password);
    static UserModel *load(void);
    static UserModel *findByPassword(QString password);

    virtual QString getUserName(void);
    virtual void save(void);
    virtual bool hasPermission(const PermissionModel p);
    virtual ~CoordinatorModel();

private:
    const int id;

    explicit CoordinatorModel(int, QString);

    static bool does_exist;
    static UserModel *coord;
};

#endif // COORDINATOR_H
