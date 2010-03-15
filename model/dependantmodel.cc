
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
 * Create a new dependant.
 */
DependantModel *DependantModel::create(QString fullName,
                                       QDateTime bday,
                                       const int memberId) {
    QSqlQuery q;
    q.prepare(
        "INSERT INTO dependant (name, date_of_21st_bday, member_id) "
        "VALUES (?, ?, ?)"
    );
    q << fullName << bday << memberId;
    q.exec();
    return findById(q.lastInsertId().toInt());
}

/**
 * Save the dependant.
 */
bool DependantModel::save(void) {
    QSqlQuery q;
    q.prepare("UPDATE dependant SET name=?,date_of_21st_bday=? WHERE id=?");
    q << name << bday_21;
    return q.exec();
}

/**
 * Get the name of the dependant.
 */
QString DependantModel::getName(void) {
    return name;
}

/**
 * Set the name of the dependant.
 */
void DependantModel::setName(QString n) {
    name = n;
}

/**
 * Get the 21st birthday.
 */
QDateTime DependantModel::getBirthday(void) {
    return bday_21;
}

/**
 * Set the birthday of the dependant.
 */
void DependantModel::setBirthday(QDateTime t) {
    bday_21 = t;
}
