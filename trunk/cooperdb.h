#ifndef COOPERDB_H
#define COOPERDB_H


//Handle all database assoicated operations
class CooperDB
{
public:
    CooperDB();
    ~CooperDB();
    static bool hasCoordinator();
};

#endif // COOPERDB_H
