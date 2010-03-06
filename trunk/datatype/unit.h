#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include "modeliterator.h"
#include "cooperdb.h"

using namespace std;

class Unit
{
public:
    ~Unit();

    typedef class ModelIterator<Unit, Unit> iterator;

    bool remove(void);
    void save(void);
    bool isEmpty();

    static void create(QString address, const int numRooms, const int id);
    static bool exists(void);
    static Unit *load(const int id);
    static pair<iterator, iterator> findAll(void);

private:
    Unit(QString streetAddress, int nRooms, const int id);

    static void remember(const int id, Unit *val);
    static Unit *recall(const int id);
    static bool remembered(const int id);

    static map<int, Unit *> elms;

    // data
    const int id;
    int num_rooms;
    QString address;
};

#endif // UNIT_H
