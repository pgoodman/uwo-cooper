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
        void create(const int uNumber, QString address, const int numRooms, const int id);

	//Constructors
	Unit();
        Unit(int roomNumber, QString address, int bedrooms);
	~Unit();

	//Attributes
	int number;
	QString streetAddress;
        int numBedrooms;
        int id;
	bool isEmpty();

	//Accessor Methods
	int getNumber() {return number;}
	QString getAddress() {return streetAddress;}
	int countRooms() {return numBedrooms;}

    private:
        Unit(int roomNumber, QString streetAddress, int nRooms, const int id);

        static void remember(const int id, Unit *val);
        static Unit *recall(const int id);
        static bool remembered(const int id);

        static map<int, Unit *> elms;

};

#endif // UNIT_H
