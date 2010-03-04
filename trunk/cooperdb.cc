
#include "cooperdb.h"
#include "criticalerror.h"

bool CooperDB::is_connected(false);
QSqlDatabase CooperDB::db;

/**
 * Connect to the database if it exists, and if it does not exist, create it.
 */
CooperDB::CooperDB() {

}

/**
 * Disconnect from the database.
 */
CooperDB::~CooperDB() {
    //db.close();
}

/**
 * Check whether or not a given query returns any rows.
 */
bool CooperDB::hasAny(const char *query) {
    return select(query).isValid();
}

/**
 * Return the result from a simple query.
 */
QSqlQuery CooperDB::select(const char *query) {
    assert(is_connected);
    QSqlQuery q(query, db);
    return q;
}

/**
 * Connect to the database, or make it if it doesn't exist.
 */
void CooperDB::connect(const char *db_name) {
    if(is_connected) {
        return;
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    if(!db.isValid()) {
        throw CriticalError("Cannot open database.", "Unable to load SQLite.");
    }
    db.setDatabaseName(db_name);
    if(!db.open()) {
        throw CriticalError(
            "Cannot open database",
            "Unable to establish a database connection."
        );
    }

    // create the db tables
    if(!db.tables().count()) {
        makeDatabase();
    }

    is_connected = true;
}

/**
 * Throw a database error from a query.
 */
void CooperDB::queryError(string header, QSqlQuery &query) {
    QString db_err(db.lastError().text() + query.executedQuery());
    throw CriticalError(header, db_err.toStdString());
}

void CooperDB::queryError(stringstream &header, QSqlQuery &query) {
    queryError(header.str(), query);
}

void CooperDB::queryError(const char *header, QSqlQuery &query) {
    queryError(string(header), query);
}

/**
 * Make the database.
 */
void CooperDB::makeDatabase() {
    const char table_names[][20] = {
        "user", "committee",
    };
    const char tables[][500] = {
        "CREATE TABLE user ("
            "full_name VARCHAR(50) NOT NULL,"
            //"last_name VARCHAR(50) NOT NULL,"

            // login info
            "name VARCHAR(50) NOT NULL,"
            "password VARCHAR(32) NOT NULL,"

            // bools
            "is_coordinator TINYINTEGER(1) NOT NULL DEFAULT 0,"
            "share_telephone TINYINTEGER(1) DEFAULT 0,"
            "is_marked TINYINTEGER(1) DEFAULT 0,"

            // member-specific
            "telephone VARCHAR(20) NOT NULL,"
            "move_in_time UNSIGNED INTEGER DEFAULT 0,"
            "money_owed REAL DEFAULT 0.0,"


            // index
            "id INTEGER PRIMARY KEY AUTOINCREMENT ON CONFLICT REPLACE,"
            "committee_id INTEGER NOT NULL DEFAULT 0"
            //"KEY(committee_id)"
        ")",

        "CREATE TABLE committee ("
            "name VARCHAR(30) NOT NULL,"
            "can_delete TINYINTEGER(1) DEFAULT 1,"
            "chair_id INTEGER NOT NULL DEFAULT 0,"
            "secretary_id INTEGER NOT NULL DEFAULT 0,"
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "member_perms INTEGER,"
            "chair_perms INTEGER"

            //"KEY(chair_id),"
            //"KEY(secretary_id)"
        ")",

    };

    size_t num_tables = sizeof(table_names) / sizeof(table_names[0]);
    stringstream error;
    QSqlQuery q(db);

    for(; num_tables--; ) {
        if(!q.exec(tables[num_tables])) {
            error << "Error creating table '"
                  << table_names[num_tables]
                  << "'.";
            queryError(error, q);
        }
    }
}

/**
 * Bind a value to a prepared statement.
 */
template <typename T> QSqlQuery &operator<< (QSqlQuery &q, T val) {
    q.addBindValue(QVariant(val));
    return q;
}
template <> QSqlQuery &operator<< <string &>(QSqlQuery &q, string &val) {
    q.addBindValue(QVariant(QString(val.c_str())));
    return q;
}
template <> QSqlQuery &operator<< <string>(QSqlQuery &q, string val) {
    q.addBindValue(QVariant(QString(val.c_str())));
    return q;
}
template <> QSqlQuery &operator<< <time_t>(QSqlQuery &q, time_t val) {
    q.addBindValue(QVariant(static_cast<unsigned int>(val)));
    return q;
}
template <> QSqlQuery &operator<< <void *>(QSqlQuery &q, void *val) {
    (void) val;
    q.addBindValue(QVariant());
    return q;
}

/**
 * Quickly get the variant from the query given a column name.
 */

/*QVariant qcol(const QSqlQuery &q, const char *index) {
    return q.value(q.record().indexOf(index));
}
*/
template<typename T> T qcol(const QSqlQuery &q, const char *index) {
    (void) q; (void) index;
    throw 0;
}
template <> QVariant qcol(const QSqlQuery &q, const char *index) {
    return q.value(q.record().indexOf(index));
}
template <> int qcol(const QSqlQuery &q, const char *index) {
    return qcol<QVariant>(q, index).toInt();
}
template <> double qcol(const QSqlQuery &q, const char *index) {
    return qcol<QVariant>(q, index).toDouble();
}
template <> bool qcol(const QSqlQuery &q, const char *index) {
    return qcol<QVariant>(q, index).toBool();
}
template <> string qcol(const QSqlQuery &q, const char *index) {
    return qcol<QVariant>(q, index).toString().toStdString();
}


/**
 * Extract thigns from the variants.
 */
const QVariant &operator>>(const QVariant &v, int &x) {
    x = v.toInt();
    return v;
}
const QVariant &operator>>(const QVariant &v, double &x) {
    x = v.toDouble();
    return v;
}
const QVariant &operator>>(const QVariant &v, bool &x) {
    x = v.toBool();
    return v;
}
const QVariant &operator>>(const QVariant &v, string &x) {
    x.assign(v.toString().toStdString());
    return v;
}
const QVariant &operator>>(const QVariant &v, QString &x) {
    x = v.toString();
    return v;
}

// tell the compiler which template instantiations to make
template QSqlQuery &operator<< <bool>(QSqlQuery &q, bool val);
template QSqlQuery &operator<< <int>(QSqlQuery &q, int val);
template QSqlQuery &operator<< <unsigned int>(QSqlQuery &q, unsigned int val);

