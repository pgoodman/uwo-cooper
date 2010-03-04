

#include "committee.h"

map<int, Committee *> Committee::elms;

/*
string name;
//name std::string[1]
bool can_delete;
Member chair;
Member secretary;
Permission chair_perms;
Permission member_perms;
list<Member> memberList;
*/

Committee::Committee(string n, const bool canDelete,
                     const perm_set_t chairPerms, const perm_set_t memberPerms,
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
        qcol<string>(q, "name"),
        qcol<bool>(q, "can_delete"),
        qcol<perm_set_t>(q, "chair_perms"),
        qcol<perm_set_t>(q, "member_perms"),
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
bool Committee::save(void) {
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
 * Return all committees.
 */
pair<Committee::iterator, Committee::iterator> Committee::findAll(void) {
    return CooperDB::selectAll<Committee,Committee>("committee", "1=1");
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

/*
Committee::Committee(string committeeName, Member committeeChair, Member committeeSecretary)
{
        name = committeeName;
        chair = committeeChair;
        secretary = committeeSecretary;
        memberList = new list<Member>;
        // Initiate chair perms and member perms
}
*/


/*
static Committee *load(int id) {
    (void) id; return 0;
}*/

/*
Permission Committee::getPermissions(Member member) {
    if (member.getID() == chair.getID()) {
        return chair_perms;
    }
    else
        return member_perms;
}

void Committee::addMember(Member member) {
    //Add a member to the committees member list.
    // NOTE: USING LIST AS EXAMPLE, DONT KNOW HOW WERE GOING TO STORE THIS!!!

    memberList.insert(member);
}

void Committee::removeMember(Member member) {
    // Remove a member from a committees member list.
    //NOTE: USING LIST AS EXAMPLE, DONT KNOW HOW WERE GOING TO STORE THIS!!!

    memberList.remove(member);
}

//void Committee::addTask(Task task);
//void Committee::removeTask(Task task);
*/
