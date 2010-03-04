#include "unit.h"

Unit::Unit()
{
}

Unit::Unit(int roomNumber, QString address, int bedrooms)
{
	number = roomNumber;
	streetAddress = address;
	numBedrooms = bedrooms;
}

Unit::~Unit() {
}
