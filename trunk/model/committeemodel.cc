
#include "model/committeemodel.h"

const char *CommitteeModel::table_name("committee");
//const char *CommitteeModel::column_names[20] = {
//    "id", "name", "can_delete", "chair_id", "secretary_id", "member_perms",
//    "chair_perms"
//};

/**
 * Private constructor, initialize a new committee from db info.
 */
CommitteeModel::CommitteeModel(QString n, const bool canDelete,
                     const PermissionModelSet chairPerms,
                     const PermissionModelSet memberPerms,
                     const int chairId, const int secretaryId,
                     const int committeeId)
 : IModel<CommitteeModel,select_from_table_tag>(committeeId), name(n),
   can_delete(canDelete), chair_perms(chairPerms),
   member_perms(memberPerms), chair_id(chairId), secretary_id(secretaryId) {
}

/**
 * Destructor.
 */
CommitteeModel::~CommitteeModel() { }

/**
 * Load a committee by its id.
 */
CommitteeModel *CommitteeModel::load(QSqlQuery &q, const int id) {
    return new CommitteeModel(
        qcol<QString>(q, "name"),
        qcol<bool>(q, "can_delete"),
        qcol<PermissionModelSet>(q, "chair_perms"),
        qcol<PermissionModelSet>(q, "member_perms"),
        qcol<int>(q, "chair_id"),
        qcol<int>(q, "secretary_id"),
        id
    );
}

/**
 * Save a committee to the database.
 */
void CommitteeModel::save(void) {
    QSqlQuery q;
    q.prepare(
        "UPDATE committee set name=?,can_delete=?,chair_perms=?,member_perms=?,"
        "chair_id=?,secretary_id=? WHERE id=?"
    );
    q << name << can_delete << chair_perms << member_perms << chair_id
      << secretary_id << id;
    if(!q.exec()) {
        Database::queryError("Unable to Save Committee", q);
    }
}

/**
 * Create an return a committee.
 */
bool CommitteeModel::create(QString n, const bool canDelete,
                            const PermissionModelSet chairPerms,
                            const PermissionModelSet memberPerms,
                            const int chairId, const int secretaryId,
                            const int committeeId) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO committee (name,can_delete,chair_perms,member_perms,"
        "chair_id,secretary_id) VALUES (?,?,?,?,?,?)"
    );
    q << n << canDelete << chairPerms << memberPerms << chairId << secretaryId
      << committeeId;
    if(!q.exec()) {
        return false;
    }
    return true;
}

/**
 * Get the permissions for a member id.
 */
PermissionModelSet CommitteeModel::getPermissions(const int member_id) {
    return member_id == chair_id ? chair_perms : member_perms;
}

/**
 * Get the name of a committee.
 */
QString CommitteeModel::toString(void) {
    return name;
}
