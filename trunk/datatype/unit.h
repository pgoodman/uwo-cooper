#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include "modeliterator.h"
#include "cooperdb.h"

using namespace std;

class Unit
{
public:
	
    typedef class ModelIterator<Unit, Unit> iterator;
    static Unit *load(const int id);
    static pair<iterator, iterator> findAll(void);

    bool remove(void);
    void save(void);
    bool isEmpty();

    static Unit *create(const int uNumber, QString address,
                       const int numRooms, const int id);

    static Unit *load(const int id);

    const QString address;
    const int num_bedrooms;
    const int id;

private:
	explicit Unit(int roomNumber, QString address, int bedrooms);
	~Unit();
};

#endif // UNIT_H
