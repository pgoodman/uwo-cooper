
#include "cooperdb.h"
#include "criticalerror.h"

/**
 * Connect to the database if it exists, and if it does not exist, create it.
 */
CooperDB::CooperDB(const char *db_name){
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
                "is_coordinator TINYINT(1) NOT NULL DEFAULT 0,"
                "share_telephone TINYINT(1) DEFAULT 0,"
                "is_marked TINYINT(1) DEFAULT 0,"

                // member-specific
                "telephone VARCHAR(20) NOT NULL,"
                "move_in_time INT DEFAULT 0,"
                "money_owed REAL DEFAULT 0.0,"


                // index
                "id INT NOT NULL DEFAULT 0 PRIMARY KEY AUTOINCREMENT,"
                "committee_id INT NOT NULL DEFAULT 0,"
                "INDEX(committee_id)"
            ")",

            "CREATE TABLE committee ("
                "name VARCHAR(30) NOT NULL,"
                "can_delete TINYINT(1) DEFAULT 1,"
                "chair_id INT NOT NULL DEFAULT 0,"
                "secretary_id INT NOT NULL DEFAULT 0,"
                "id INT NOT NULL PRIMARY KEY AUTOINCREMENT,"
                "member_perms INT,"
                "chair_perms INT,"

                "INDEX(chair_id),"
                "INDEX(secretary_id)"
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
}

/**
 * Disconnect from the database.
 */
CooperDB::~CooperDB(){
    db.close();
}

bool CooperDB::hasCoordinator(){

    return false;
    //return true;
}
