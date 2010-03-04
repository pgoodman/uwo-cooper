#ifndef COMMITTEE_H
#define COMMITTEE_H

#include <utility>
#include <string>

#include <QSqlQuery>

#include "cooperdb.h"

#include "permission.h"
#include "modeliterator.h"

using namespace std;

class Member;

class Committee
{
public:
    typedef class ModelIterator<Committee, Committee> iterator;

    static Committee *load(const int id);
    static pair<iterator, iterator> findAll(void);
    bool remove(void);
    bool save(void);

private:
    Committee(string n, const bool canDelete, const perm_set_t chairPerms,
              const perm_set_t memberPerms, const int chair_id,
              const int secretary_id, const int committeeId);

    ~Committee();

    static void remember(const int id, Committee *val);
    static Committee *recall(const int id);
    static bool remembered(const int id);

    //static Committee *load(int id) { (void) id; return 0; }
   /* Permission getPermissions(Member member);
    void addMember(Member member);
    void removeMember(Member member);
   // void addTask(Task task);
   // void removeTask(Task task);
    */

    string name;
    bool can_delete;

    Member *chair;
    Member *secretary;

    perm_set_t chair_perms;
    perm_set_t member_perms;

    int chair_id;
    int secretary_id;
    const int id;

    static map<int, Committee *> elms;
};


#endif // COMMITTEE_H
