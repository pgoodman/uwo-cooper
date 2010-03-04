#ifndef COMMITTEE_H
#define COMMITTEE_H

#include <utility>
#include <QString>

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
    void save(void);
    void create(QString n, const bool canDelete,
                const perm_set_t chairPerms, const perm_set_t memberPerms,
                const int chairId, const int secretaryId,
                const int committeeId);

private:
    Committee(QString n, const bool canDelete, const perm_set_t chairPerms,
              const perm_set_t memberPerms, const int chair_id,
              const int secretary_id, const int committeeId);

    ~Committee();

    static void remember(const int id, Committee *val);
    static Committee *recall(const int id);
    static bool remembered(const int id);

    QString name;
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
