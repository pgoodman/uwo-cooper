#ifndef UNIT_H
#define UNIT_H

#include <QString>

#include "lib/database.h"
#include "lib/imodel.h"

using namespace std;

class UnitModel;
class UnitModel : public IModel<UnitModel>
{
    friend class IModel<UnitModel>;

public:
    static const char *table_name;
    ~UnitModel();

    bool isEmpty(void);
    virtual void save(void);

    static void create(QString address, const int numRooms, const int number);
    static bool exists(void);
    static UnitModel *findByLocation(const int number, QString address);

    QString toString(void);

    // data
    const int number;
    const int num_rooms;
    const QString address;

protected:
    static UnitModel *load(QSqlQuery &q, const int id);

private:
    UnitModel(QString streetAddress, int nRooms, const int id, const int num);
};

#endif // UNIT_H
