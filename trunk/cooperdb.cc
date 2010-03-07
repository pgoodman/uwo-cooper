
#include "cooperdb.h"

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
 * Disconnect the database.
 */
void CooperDB::close(void) {
    db.close();
}

/**
 * Check whether or not a given query returns any rows.
 */
bool CooperDB::hasAny(const char *query) {
    return select(query).first();
}

/**
 * Return the result from a simple query.
 */
QSqlQuery CooperDB::select(const char *query) {
    assert(is_connected);
    QSqlQuery q(db);
    if(!q.exec(query)) {
        queryError("Invalid Query", q);
    }
    return q;
}

QSqlQuery CooperDB::select(const char *table, const char *cond) {
    assert(is_connected);
    stringstream ss;
    ss << "SELECT * FROM " << table << " WHERE " << cond;
    QSqlQuery q(db);
    if(!q.exec(ss.str().c_str())) {
        queryError("Invalid Query", q);
    }
    q.first();
    return q;
}

/**
 * Return the result from a simple query.
 */
bool CooperDB::remove(const char *table, const int id) {
    assert(is_connected);
    stringstream ss;
    ss << "DELETE FROM " << table << " WHERE id=" << id;
    QSqlQuery q(ss.str().c_str());
    return q.exec();
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
 * Add in the committees.
 */
static void install_committees(QSqlQuery &q) {
    PermissionSet chair_perms(0
        | EDIT_COMMITTEE_CHAIR
        | EDIT_COMMITTEE_SECRETARY
        | ADD_TASK
        | PRINT_TASK_LIST
    );
    PermissionSet member_perms(0
        | PRINT_PUBLIC_LIST
        | PRINT_COMMITTEE_LIST
    );
    PermissionSet education_chair_perms(chair_perms
        | INIT_MEMBER_COMMITTEE
    );

    // chair can: everything
    q.prepare(
        "INSERT INTO committee (name,can_delete,member_perms,chair_perms) "
        "VALUES ('Board',0,?,33554431)"
    );
    q << member_perms;
    q.exec();

    q.prepare(
        "INSERT INTO committee (name,can_delete,member_perms,chair_perms) "
        "VALUES ('Inspections',0,?,?)"
    );
    q << member_perms << chair_perms;
    q.exec();

    q.prepare(
        "INSERT INTO committee (name,can_delete,member_perms,chair_perms) "
        "VALUES ('Membership',0,?,?)"
    );
    q << member_perms << chair_perms;
    q.exec();

    q.prepare(
        "INSERT INTO committee (name,can_delete,member_perms,chair_perms) "
        "VALUES ('Education',0,?,?)"
    );
    q << member_perms << education_chair_perms;
    q.exec();

    q.prepare(
        "INSERT INTO committee (name,can_delete,member_perms,chair_perms) "
        "VALUES ('Member Relations',0,?,?)"
    );
    q << member_perms << chair_perms;
    q.exec();
}

/**
 * Install tables.
 */
static void install_tables(QSqlQuery &q) {
    const char table_names[][20] = {
        "user", "committee", "unit"
    };
    const char tables[][500] = {
        "CREATE TABLE user ("
            "first_name TEXT,"
            "last_name TEXT,"

            // login info
            "name TEXT,"
            "password TEXT,"

            // bools
            "is_coordinator INTEGER DEFAULT 0,"
            "share_telephone INTEGER DEFAULT 0,"
            "is_marked INTEGER DEFAULT 0,"

            // member-specific
            "telephone TEXT,"
            "move_in_time INTEGER DEFAULT 0,"
            "money_owed REAL DEFAULT 0.0,"


            // index
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "committee_id INTEGER DEFAULT 0,"

            "UNIQUE(name)"
            //"KEY(committee_id)"
        ")",

        "CREATE TABLE committee ("
            "name TEXT,"
            "can_delete INTEGER DEFAULT 1,"
            "chair_id INTEGER DEFAULT 0,"
            "secretary_id INTEGER DEFAULT 0,"
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "member_perms INTEGER,"
            "chair_perms INTEGER"

            //"KEY(chair_id),"
            //"KEY(secretary_id)"
        ")",

        "CREATE TABLE unit ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "address TEXT,"
            "num_rooms INTEGER"
        ")"
    };

    size_t num_tables = sizeof(table_names) / sizeof(table_names[0]);
    D( cout << "Num Tables: " << num_tables << endl; )
    stringstream error;

    for(; num_tables--; ) {
        if(!q.exec(tables[num_tables])) {
            error << "Error creating table '"
                  << table_names[num_tables]
                  << "'.";
            CooperDB::queryError(error, q);
        }
    }
}

/**
 * Make the database.
 */
void CooperDB::makeDatabase() {
    QSqlQuery q(db);

    install_tables(q);
    install_committees(q);

    D(
        q.exec(
            "INSERT INTO user (first_name,last_name,name, password, "
            "share_telephone,telephone, move_in_time) VALUES ('Peter',"
            "'Goodman','peter','peter',0,'519-933-0204',0)"
        );
        q.exec(
            "INSERT INTO user (first_name,last_name, name, password, "
            "share_telephone, telephone, move_in_time) VALUES ('Stephan',"
            "'Beltran','stephan','stephan', 1,'',0)"
        );
        q.exec(
            "INSERT INTO user (first_name,last_name, name, password, "
            "share_telephone, telephone, move_in_time) VALUES ('Nick',"
            "'Perreault','nick','nick', 1,'',0)"
        );
        q.exec(
            "INSERT INTO user (first_name,last_name, name, password, "
            "share_telephone, telephone, move_in_time) VALUES ('Jason','Lu',"
            "'jason','jason', 0,'',0)"
        );
    )
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
    //cout << q.executedQuery().toStdString() << endl;
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

