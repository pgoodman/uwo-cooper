
#include "unit.h"
#include "cooperdb.h"

/**
 * Constructor
 */
Unit::Unit(int unitId, QString streetAddress, int bedrooms)
: id(unitId), address(streetAddress), num_bedrooms(bedrooms)
{ }

/**
 * Destructor.
 */
Unit::~Unit() {
}

/**
 * Save a unit to the database.
 */
void Unit::save(void)
{
    QSqlQuery q;
    q.prepare("UPDATE unit set address=?,num_rooms=? WHERE id=?");
    q << address << num_bedrooms << id;
    if(!q.exec()) {
        CooperDB::queryError("Unable to Save Unit", q);
    }
}

/**
 * Create a new unit.
 */
Unit *Unit::create(int rNumber, QString address, int nRooms, int id) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO unit (id,number,address,num_rooms)"
        "VALUES (?,?,?,?)"
    );
    q << id << rNumber << address << nRooms;

    if(!q.exec()) {
        CooperDB::queryError("Unable to Add Committee", q);
    }

    return Unit::load(id);
}

/**
 * Load a unit from the databse by its id.
 */
Unit *Unit::load(const int id) {
    /*if(remembered(id)) {
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
        id,
        qcol<QString>(q, "address"),
        qcol<int>(q, "num_rooms")
    );

    remember(id, c);
    return c;*/
    (void) id;
    return 0;
}


/**
 * Return all committees.
 */
pair<Unit::iterator, Unit::iterator> Unit::findAll(void) {
    return CooperDB::selectAll<Unit>("unit", "1=1");
}
