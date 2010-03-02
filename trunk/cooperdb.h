#ifndef COOPERDB_H
#define COOPERDB_H

#include <QSqlDatabase>

//Handle all database assoicated operations
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
