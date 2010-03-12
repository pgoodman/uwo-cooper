
#ifndef COMMITTEE_H
#define COMMITTEE_H

#include <utility>

#include <QString>
#include <QSqlQuery>

#include "lib/database.h"
#include "lib/imodel.h"

#include "model/permissionmodel.h"

using namespace std;

class MemberModel;

class CommitteeModel : public IModel<CommitteeModel, select_from_table_tag> {

    MODEL_CLASS(CommitteeModel);

public:
    static const char *table_name;

    virtual void save(void);
    bool create(QString n, const bool canDelete,
                const PermissionModelSet chairPerms,
                const PermissionModelSet memberPerms,
                const int chairId, const int secretaryId,
                const int committeeId);

    PermissionModelSet getPermissions(const int member_id);
    QString toString(void);
    
    virtual ~CommitteeModel();

protected:
    static CommitteeModel *load(QSqlQuery &q, const int id);

private:
    explicit CommitteeModel(QString n, const bool canDelete,
                            const PermissionModelSet chairPerms,
                            const PermissionModelSet memberPerms, 
                            const int chair_id, const int secretary_id, 
                            const int committeeId);

    QString name;
    bool can_delete;

    MemberModel *chair;
    MemberModel *secretary;

    PermissionModelSet chair_perms;
    PermissionModelSet member_perms;

    int chair_id;
    int secretary_id;
};

#endif // COMMITTEE_H
