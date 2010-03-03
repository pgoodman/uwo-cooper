#ifndef COOPERDB_H
#define COOPERDB_H

#include <stdexcept>
#include <sstream>

#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>

#include <assert.h>

#include "criticalerror.h"

/**
 * Handle creating, connecting, and querying the cooper database.
 */
class CooperDB
{
public:
    ~CooperDB();

    static void connect(const char *);
    static bool hasCoordinator();
private:
    CooperDB();

    static QSqlDatabase db;
    static void makeDatabase();
    static bool is_connected;
};

#endif // COOPERDB_H
