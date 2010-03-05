

#include "committee.h"

map<int, Committee *> Committee::elms;

/**
 * Private constructor, initialize a new committee from db info.
 */
Committee::Committee(QString n, const bool canDelete,
                     const PermissionSet chairPerms, const PermissionSet memberPerms,
                     const int chairId, const int secretaryId,
                     const int committeeId)
: name(n), can_delete(canDelete), chair_perms(chairPerms),
  member_perms(memberPerms), chair_id(chairId), secretary_id(secretaryId),
  id(committeeId) {
}

/**
 * Destructor.
 */
Committee::~Committee() { }

/**
 * Load a committee by its id.
 */
Committee *Committee::load(const int id) {
    if(remembered(id)) {
        return recall(id);
    }

    QSqlQuery q;
    q.prepare("SELECT * FROM committee WHERE id=?");
    q << id;
    if(!q.exec()) {
        return 0;
    }

    Committee *c = new Committee(
        qcol<QString>(q, "name"),
        qcol<bool>(q, "can_delete"),
        qcol<PermissionSet>(q, "chair_perms"),
        qcol<PermissionSet>(q, "member_perms"),
        qcol<int>(q, "chair_id"),
        qcol<int>(q, "secretary_id"),
        id
    );
    remember(id, c);
    return c;
}

/**
 * Save a committee to the database.
 */
void Committee::save(void) {
    QSqlQuery q;
    q.prepare(
        "UPDATE committee set name=?,can_delete=?,chair_perms=?,member_perms=?,"
        "chair_id=?,secretary_id=? WHERE id=?"
    );
    q << name << can_delete << chair_perms << member_perms << chair_id
      << secretary_id << id;
    if(!q.exec()) {
        CooperDB::queryError("Unable to Save Committee", q);
    }
}

/**
 * Create an return a committee.
 */
void Committee::create(QString n, const bool canDelete,
                       const PermissionSet chairPerms,
                       const PermissionSet memberPerms,
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
        CooperDB::queryError("Unable to Add Committee", q);
    }
}

/**
 * Return all committees.
 */
pair<Committee::iterator, Committee::iterator> Committee::findAll(void) {
    return CooperDB::selectAll<Committee>("committee", "1=1");
}

bool Committee::remove(void) {
    elms.erase(id);
    return CooperDB::remove("committee", id);
}

/**
 *
 */
void Committee::remember(const int id, Committee *val) {
    if(!remembered(id)) {
        elms[id] = val;
    }
}

Committee *Committee::recall(const int id) {
    if(!remembered(id)) {
        throw 0;
    }
    return elms[id];
}

bool Committee::remembered(const int id) {
    return elms.end() != elms.find(id);
}

/**
 * Get the permissions for a member id.
 */
PermissionSet Committee::getPermissions(const int member_id) {
    return member_id == chair_id ? chair_perms : member_perms;
}

/**
 * Get the name of a committee.
 */
QString Committee::toString(void) {
    return name;
}
