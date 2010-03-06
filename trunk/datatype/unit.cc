#include "unit.h"
#include "cooperdb.h"

map<int, Unit *> Unit::elms;

Unit::Unit(QString streetAddress, int numRooms, const int unitId)
 : id(unitId), num_rooms(numRooms), address(streetAddress) { }

/**
 * Return whether or not any units exist.
 */
bool Unit::exists(void) {
    return CooperDB::hasAny("SELECT * FROM unit");
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
        qcol<QString>(q, "address"),
        qcol<int>(q, "num_rooms"),
        id
    );

    remember(id, c);
    return c;
}

void Unit::save(void)
{
    QSqlQuery q;
    q.prepare("UPDATE unit SET address=?,num_rooms=? WHERE id=?");
    q << address << num_rooms << id;
    if(!q.exec()) {
        CooperDB::queryError("Unable to Save Unit", q);
    }
}

void Unit::create(QString addr, int nRooms, int id) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO unit (address,num_rooms,id)"
        "VALUES (?,?,?)"
    );
    q << addr << nRooms << id;

    if(!q.exec()) {
        CooperDB::queryError("Unable to Add Committee", q);
    }
    q.finish();

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
