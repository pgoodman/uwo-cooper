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
