
#include "cooperdb.h"

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
