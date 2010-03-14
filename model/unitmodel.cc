
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
    return new UnitModel(
        qcol<QString>(q, "address"),
        qcol<int>(q, "num_rooms"),
        id,
        qcol<int>(q, "num_members") // synthesized through unit_select view
    );
}

/**
 * Create a new unit.
 */
UnitModel *UnitModel::create(QString address, int num_rooms, const int id) {
    QSqlQuery q;
    q.prepare("INSERT INTO unit (address,num_rooms,id) VALUES (?,?,?)");
    q << address << num_rooms << id;
    if(!q.exec()) {
        return 0;
    }
    q.finish();
    return findById(id);
}

/**
 * Save the unit.
 */
bool UnitModel::save(void) {
QSqlQuery q;
    q.prepare("UPDATE unit SET address=?, num_rooms=? WHERE id=?");
    q << address << num_rooms << id;
    return q.exec();
}

/**
 * Units cannot be removed so do nothing.
 */
bool UnitModel::remove(void) {
    return false;
}

/**
 * Check whether or not the unit is empty.
 */
bool UnitModel::isEmpty(void) {
    return 0 == num_members;
}

/**
 * Update the number of members in this unit but an increment.
 */
void UnitModel::updateNumTenants(int increment) {
    num_members += increment;
}

/**
 * Return a string representation of this unit.
 */
QString UnitModel::toString(void) {
    stringstream ss;
    ss << "Unit " << id << " at " << address.toStdString() << " ";
    if(0 == num_members) {
        ss << "[empty]";
    } else {
        ss << "[" << num_members << " tenants]";
    }
    return QString(ss.str().c_str());
}

UnitModel::~UnitModel() {
}
