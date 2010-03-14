
#include "model/dependantmodel.h"

const char *DependantModel::table_name = "dependant";

/**
 * Private constructor.
 */
DependantModel::DependantModel(const int id,
                               QString fullName,
                               QDateTime bday,
                               const int memberId)
 : IModel<DependantModel,select_from_table_tag>(id),
   name(fullName), bday_21(bday), member_id(memberId) { }

/**
 * Check whether this dependent is under age.
 */
bool DependantModel::isUnderAge(void) {
    QDateTime now;
    now.setTime_t(time(0));
	return bday_21 < now;
}

/**
 * Convert this dependent to a string.
 */
QString DependantModel::toString(void) {
    return name;
}

/**
 * Load a dependant from the database.
 */
DependantModel *DependantModel::load(QSqlQuery &q, const int id) {
    return new DependantModel(
        id,
        qcol<QString>(q, "name"),
        qcol<QDateTime>(q, "date_of_21st_bday"),
        qcol<int>(q, "member_id")
    );
}

/**
 * Save the dependant.
 */
bool DependantModel::save(void) {
    return true;
}

/**
 * Remove the dependant.
 */
bool DependantModel::remove(void) {
    return true;
}


