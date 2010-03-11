
#include "lib/database.h"

bool Database::is_connected(false);
QSqlDatabase Database::db;

/**
 * Connect to the database if it exists, and if it does not exist, create it.
 */
Database::Database() {

}

/**
 * Disconnect from the database.
 */
Database::~Database() {
    //db.close();
}

/**
 * Disconnect the database.
 */
void Database::disconnect(void) {
    db.close(); // disconnected current db
    db = QSqlDatabase(); // reassigns default db to stop that annoying error
}

/**
 * Check whether or not a given query returns any rows.
 */
bool Database::hasAny(const char *query) {
    return select(query).first();
}

/**
 * Return the result from a simple query.
 */
QSqlQuery Database::select(const char *query) {
    assert(is_connected);
    QSqlQuery q(db);
    q.exec(query);
    q.first();
    return q;
}

QSqlQuery Database::select(const char *table, const char *cond) {
    assert(is_connected);
    stringstream ss;
    ss << "SELECT * FROM " << table << " WHERE " << cond;
    return select(ss.str().c_str());
}

QSqlQuery Database::select(const char *table, const int id) {
    assert(is_connected);
    stringstream ss;
    ss << "id=" << id;
    return select(table, ss.str().c_str());
}

/**
 * Return the result from a simple query.
 */
bool Database::remove(const char *table, const int id) {
    assert(is_connected);
    stringstream ss;
    ss << "DELETE FROM " << table << " WHERE id=" << id;
    QSqlQuery q(ss.str().c_str());
    return q.exec();
}

/**
 * Connect to the database, or make it if it doesn't exist. If it needs to
 * create the database then it calls the function pointer make_db passed in.
 */
void Database::connect(const char *db_name,
                       const char *type,
                       install_func_t *make_db) {
    if(is_connected) {
        return;
    }

    db = QSqlDatabase::addDatabase(type);
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
        QSqlQuery q;
        make_db(q);
    }

    is_connected = true;
}

/**
 * Throw a database error from a query.
 */
void Database::queryError(string header, QSqlQuery &query) {
    QString db_err(db.lastError().text() + query.executedQuery());
    throw CriticalError(header, db_err.toStdString());
}

void Database::queryError(stringstream &header, QSqlQuery &query) {
    queryError(header.str(), query);
}

void Database::queryError(const char *header, QSqlQuery &query) {
    queryError(string(header), query);
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
template <> unsigned int qcol(const QSqlQuery &q, const char *index) {
    return qcol<QVariant>(q, index).toUInt();
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
template <> QString qcol(const QSqlQuery &q, const char *index) {
    return qcol<QVariant>(q, index).toString();
}
template <> long qcol(const QSqlQuery &q, const char *index) {
    return qcol<QVariant>(q, index).toUInt();
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
template QSqlQuery &operator<< <double>(QSqlQuery &q, double val);
template QSqlQuery &operator<< <unsigned int>(QSqlQuery &q, unsigned int val);
template QSqlQuery &operator<< <QString>(QSqlQuery &q, QString val);

