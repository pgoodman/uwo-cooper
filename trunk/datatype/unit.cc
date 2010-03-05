#include "unit.h"
#include "cooperdb.h"

map<int, Unit *> Unit::elms;

Unit::Unit()
{
}

Unit::Unit(int roomNumber, QString address, int bedrooms)
{
	number = roomNumber;
	streetAddress = address;
	numBedrooms = bedrooms;
}

Unit::Unit(int rNumber, QString address, int numRooms, const int ID)
{
    number = rNumber;
    streetAddress = address;
    numBedrooms = numRooms;
    id = ID;
}

Unit *Unit::load(const int id) {

    QSqlQuery q;
    q.prepare("SELECT * FROM unit WHERE id=?");
    q << id;
    if(!q.exec()) {
        return 0;
    }
    q.first();
    Unit *c = new Unit(
        qcol<int>(q, "roomNumber"),
        qcol<QString>(q, "streetAddress"),
        qcol<int>(q, "numBedrooms"),
        id
    );

    remember(id, c);
    return c;
}

void Unit::save(void)
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
 * Return all Units.
 */
pair<Unit::iterator, Unit::iterator> Unit::findAll(void) {
    return CooperDB::selectAll<Unit>("unit", "1=1");
}


void Unit::remember(const int id, Unit *val) {
    if(!remembered(id)) {
        elms[id] = val;
    }
}

Unit *Unit::recall(const int id) {
    if(!remembered(id)) {
        throw 0;
    }
    return elms[id];
}

bool Unit::remembered(const int id) {
    return elms.end() != elms.find(id);
}

Unit::~Unit() {
}
