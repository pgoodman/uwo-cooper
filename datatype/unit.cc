#include "unit.h"
#include "cooperdb.h"
Unit::Unit()
{
}

Unit::Unit(int roomNumber, QString address, int bedrooms)
{
	number = roomNumber;
	streetAddress = address;
	numBedrooms = bedrooms;
}

Unit::save(void)
{
    QSqlQuery q;
    q.prepare(
            "UPDATE unit set number=?,streetAddress=?,numBedrooms=?,id=?");
    q << number << streetAddress << numBedrooms << id;

    if(!q.exec()) {
        CooperDB::queryError("Unable to Save Unit", q);
    }
}

void Unit::create(int rNumber, QString address, int nRooms, int id) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO unit (number,streetAddress,numBedrooms,id)"
        "VALUES (?,?,?,?)"
    );
    q << rNumber << address << nRooms << id;

    if(!q.exec()) {
        CooperDB::queryError("Unable to Add Committee", q);
    }
}

Unit::~Unit() {
}
