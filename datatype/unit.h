#ifndef UNIT_H
#define UNIT_H

#include <string>

using namespace std;

class Unit
{
public:
    public:
	
	//Constructors
	Unit();
	Unit(int roomNumber, string address, int bedrooms);

	//Attributes
	int number;
	string streetAddress;
	int numBedrooms;
	bool isEmpty();

	//Accessor Methods
	int getNumber() {return number;}
	string getAddress() {return streetAddress;}
	int countRooms() {return numBedrooms;}
};

#endif // UNIT_H
