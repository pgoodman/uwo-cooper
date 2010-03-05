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

    static Unit *load(const int id);
    static pair<iterator, iterator> findAll(void);
    static Unit *create(const int uNumber, QString address,
                        const int numRooms, const int id);

    const int id;
    const QString address;
    const int num_bedrooms;

private:
	explicit Unit(int roomNumber, QString address, int bedrooms);

};

#endif // UNIT_H
