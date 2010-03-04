#ifndef UNIT_H
#define UNIT_H

#include <QString>

using namespace std;

class Unit
{
    public:
	
	//Constructors
	Unit();
	Unit(int roomNumber, QString address, int bedrooms);
	~Unit();

	//Attributes
	int number;
	QString streetAddress;
	int numBedrooms;
	bool isEmpty();

	//Accessor Methods
	int getNumber() {return number;}
	QString getAddress() {return streetAddress;}
	int countRooms() {return numBedrooms;}

};

#endif // UNIT_H
