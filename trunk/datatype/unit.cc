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

Unit *Unit::load(const int id) {
    if(remembered(id)) {
        return recall(id);
    }

    QSqlQuery q;
    q.prepare("SELECT * FROM unit WHERE id=?");
    q << id;
    if(!q.exec()) {
        return 0;
    }
    q.first();
    Unit *c = new Unit(
        qcol<QString>(q, "streetAddress"),
        qcol<int>(q, "roomNumber"),
        qcol<int>(q, "numBedrooms"),
        qcol<int>(q, "id"),
        id
    );

    remember(id, c);
    return c;
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

/**
 * Return all committees.
 */
pair<Unit::iterator, Unit::iterator> Unit::findAll(void) {
    return CooperDB::selectAll<Unit>("unit", "1=1");
}

Unit::~Unit() {
}
