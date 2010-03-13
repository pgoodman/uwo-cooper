
#include "model/committeemodel.h"

const char *CommitteeModel::table_name("committee");

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
bool CommitteeModel::save(void) {
    QSqlQuery q;
    q.prepare(
        "UPDATE committee set name=?,can_delete=?,chair_perms=?,member_perms=?,"
        "chair_id=?,secretary_id=? WHERE id=?"
    );
    q << name << can_delete << chair_perms << member_perms << chair_id
      << secretary_id << id;
    return q.exec();
}

/**
 * Create an return a committee.
 */
bool CommitteeModel::create(QString n, const bool canDelete,
                            const PermissionModelSet chairPerms,
                            const PermissionModelSet memberPerms,
                            const int chairId, const int secretaryId)
{
    QSqlQuery q;
    q.prepare(
        "INSERT INTO committee (name,can_delete,chair_perms,member_perms,"
        "chair_id,secretary_id) VALUES (?,?,?,?,?,?)"
    );
    q << n << canDelete << chairPerms << memberPerms << chairId << secretaryId;
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
 * Add a task to this committee.
 */
bool CommitteeModel::addTask(QString name,
                             QString description,
                             QDateTime deadline) const {
    return TaskModel::create(name, description, deadline, id);
}

/**
 * Ger all of a committee's tasks.
 */
TaskModel::iterator_range CommitteeModel::findTasks(void) {
    stringstream ss;
    ss << "committee_id=" << id;
    return TaskModel::findAll(ss.str().c_str());
}


/**
 * Get the name of a committee.
 */
QString CommitteeModel::toString(void) {
    return name;
}

/**
 * Return whether or not the committee can be removed.
 */
bool CommitteeModel::canRemove(void) const {
    return can_delete;
}

int CommitteeModel::getCommitteeIDFromName(QString cname) {

    QSqlQuery q;
    q.prepare("SELECT id FROM committee WHERE name=?");
    q << cname;
    if(!q.exec() || !q.first()) {
        return -1;
    }

    return qcol<int>(q, "id");
}

bool CommitteeModel::removeEntireCommittee()
{
    QSqlQuery q;
    stringstream search;
    search << "committee_id=" << id;

    MemberModel::iterator_range it(MemberModel::findAll(search.str().c_str()));

    q.prepare("DELETE FROM tasks WHERE committee_id = ?");
    q << id;
    if(!q.exec()) {
        return false;
    }

    this->remove();

    return true;
}
