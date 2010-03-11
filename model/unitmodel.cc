
#include "model/unitmodel.h"

const char *UnitModel::table_name("unit");

/**
 * Construct a unit.
 */
UnitModel::UnitModel(QString streetAddress, int numRooms, 
                     const int unitId, const int num)
 : IModel<UnitModel>(unitId), number(num),
   num_rooms(numRooms), address(streetAddress) { }

/**
 * Return whether or not any units exist.
 */
bool UnitModel::exists(void) {
    return Database::hasAny("SELECT * FROM unit");
}

/**
 * Load a unit by its address.
 */
UnitModel *UnitModel::findByLocation(const int number, QString address) {
    QSqlQuery q;
    q.prepare("SELECT * FROM unit WHERE number=? AND address=?");
    q << number << address;
    if(!q.exec() || !q.first()) {
        return 0;
    }
    return load(q, qcol<int>(q, "id"));
}

/**
 * Load a unit by query.
 */
UnitModel *UnitModel::load(QSqlQuery &q, const int id) {
    UnitModel *c = new UnitModel(
        qcol<QString>(q, "address"),
        qcol<int>(q, "num_rooms"),
        id,
        qcol<int>(q, "number")
    );
    return c;
}

/**
 * Create a new unit.
 */
void UnitModel::create(QString addr, int nRooms, const int num) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO unit (address,num_rooms,number)"
        "VALUES (?,?,?)"
    );
    q << addr << nRooms << num;
    if(!q.exec()) {
        Database::queryError("Unable to Add Unit", q);
    }
    q.finish();
}

void UnitModel::save(void) {
    // TODO
}

/**
 * Return a string representation of this unit.
 */
QString UnitModel::toString(void) {
    return number + " " + address;
}

UnitModel::~UnitModel() {
}
