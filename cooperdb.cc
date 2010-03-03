
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
CooperDB::~CooperDB(){
    db.close();
}

/**
 * Check whether or not a given query returns any rows.
 */

bool CooperDB::hasCoordinator(){
    assert(is_connected);
    QSqlQuery q("SELECT * FROM user WHERE is_coordinator=1", db);
    return q.size() > 0;
}

/**
 * Connect to the database, or make it if it doesn't exist.
 */
void CooperDB::connect(const char *db_name) {
    if(is_connected) {
        return;
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
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
 * Make the database.
 */
void CooperDB::makeDatabase() {
    const char table_names[][20] = {
        "user", "committee",
    };
    const char tables[][500] = {
        "CREATE TABLE user ("
            "first_name VARCHAR(50) NOT NULL,"
            "last_name VARCHAR(50) NOT NULL,"

            // login info
            "name VARCHAR(50) NOT NULL,"
            "password VARCHAR(32) NOT NULL,"

            // bools
            "TINYINTEGER(1) NOT NULL DEFAULT 0,"
            "share_telephone TINYINTEGER(1) DEFAULT 0,"
            "is_marked TINYINTEGER(1) DEFAULT 0,"

            // member-specific
            "telephone VARCHAR(20) NOT NULL,"
            "move_in_time INTEGER DEFAULT 0,"
            "money_owed REAL DEFAULT 0.0,"


            // index
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
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
            QString db_err(q.lastError().databaseText());
            throw CriticalError(error.str(), db_err.toStdString());
        }
    }
}
