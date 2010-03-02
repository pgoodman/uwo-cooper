
#include "cooperdb.h"

/**
 * Connect to the database if it exists, and if it does not exist, create it.
 */
CooperDB::CooperDB(const char *db_name){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_name);
    if(!db.open()) {
        /*throw runtime_error();
        QMessageBox::critical(
            0,
            qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection."),
            QMessageBox::Cancel
        );*/
    }
}

/**
 * Disconnect from the database.
 */
CooperDB::~CooperDB(){

}

bool CooperDB::hasCoordinator(){

    return false;
    //return true;
}
