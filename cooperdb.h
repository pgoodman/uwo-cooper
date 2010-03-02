#ifndef COOPERDB_H
#define COOPERDB_H

#include <stdexcept>
#include <QSqlDatabase>

#include "criticalerror.h"

/**
 * Handle creating, connecting, and querying the cooper database.
 */
class CooperDB
{
public:
    CooperDB(const char *db_name);
    ~CooperDB();
    static bool hasCoordinator();
private:
    QSqlDatabase db;
};

#endif // COOPERDB_H
