
#include "model/unitmodel.h"

const char *UnitModel::table_name("unit");
const char *UnitModel::view_name("unit_select");
//const char *UnitModel::column_names[20] = {
//    "id", "address", "num_rooms"
//};

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
        qcol<int>(q, "num_members") // synthesized through unit_select view
    );
    return c;
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

void UnitModel::save(void) {
    // TODO
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
