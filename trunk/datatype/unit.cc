#include "unit.h"

Unit::Unit()
{
}

Unit::Unit(int roomNumber, string address, int bedrooms)
{
	number = roomNumber;
	streetAddress = address;
	numBedrooms = bedrooms;
}

Unit::~Unit()
{
	delete number;
	delete streetAddress;
	delete numBedrooms;
}
