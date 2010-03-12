
#ifndef COMMITTEE_H
#define COMMITTEE_H

#include <sstream>

#include <QDateTime>
#include <QString>
#include <QSqlQuery>

#include "lib/database.h"
#include "lib/imodel.h"

#include "model/permissionmodel.h"
#include "model/taskmodel.h"

using namespace std;

class MemberModel;

class CommitteeModel : public IModel<CommitteeModel, select_from_table_tag> {

    MODEL_CLASS(CommitteeModel);

public:
    static const char *table_name;

    virtual bool save(void);

    static bool create(QString n, const bool canDelete,
                const PermissionModelSet chairPerms,
                const PermissionModelSet memberPerms,
                const int chairId, const int secretaryId);

    bool addTask(QString name, QString description, QDateTime deadline) const;

    TaskModel::iterator_range findTasks(void);

    PermissionModelSet getPermissions(const int member_id);
    QString toString(void);
    
    virtual ~CommitteeModel();

    static const int BOARD_COMMITTEE_ID = 1;
    static const int INSPECTIONS_COMMITTEE_ID = 2;
    static const int MEMBERSHIP_COMMITTEE_ID = 3;
    static const int EDUCATION_COMMITTEE_ID = 4;
    static const int MEMBER_RELATIONS_COMMITTEE_ID = 5;

protected:

    //static const char *column_names[20];
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
