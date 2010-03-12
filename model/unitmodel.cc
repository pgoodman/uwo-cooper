
#include "model/unitmodel.h"

const char *UnitModel::table_name("unit");
const char *UnitModel::view_name("unit_select");

/**
 * Construct a unit.
 */
UnitModel::UnitModel(QString streetAddress, const int numRooms,
                     const int unitId, const int numMembers)
 : IModel<UnitModel,select_from_view_tag>(unitId), num_rooms(numRooms),
   num_members(numMembers), address(streetAddress)  { }

/**
 * Return whether or not any units exist.
 */
bool UnitModel::exists(void) {
    return Database::hasAny("SELECT * FROM unit");
}

/**
 * Load a unit by query.
 */
UnitModel *UnitModel::load(QSqlQuery &q, const int id) {
    UnitModel *c = new UnitModel(
        qcol<QString>(q, "address"),
        qcol<int>(q, "num_rooms"),
        id,
        0
    );
    return c;
}

/**
 * Create a new unit.
 */
UnitModel *UnitModel::create(QString addr, int nRooms, const int id) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO unit (address,num_rooms,id)"
        "VALUES (?,?,?)"
    );
    q << addr << nRooms << id;
    if(!q.exec()) {
        Database::queryError("Unable to Add Unit", q);
    }
    q.finish();
    return findById(id);
}

void UnitModel::save(void) {
    // TODO
}

/**
 * Return a string representation of this unit.
 */
QString UnitModel::toString(void) {
    /*stringstream ss;
    ss << id << "(" << address.toStdString() << ") ";
    if(0 == num_members) {
        ss << "[empty]";
    } else {
        ss << "[" << num_members << " tenants]";
    }
    return QString(ss.str().c_str());*/
    return address;
}

UnitModel::~UnitModel() {
}
