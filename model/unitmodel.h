#ifndef UNIT_H
#define UNIT_H

#include <sstream>

#include <QString>

#include "lib/database.h"
#include "lib/imodel.h"

using namespace std;

class UnitModel : public IModel<UnitModel, select_from_view_tag>
{
    MODEL_CLASS(UnitModel);

public:
    static const char *table_name;
    static const char *view_name;

    ~UnitModel();

    bool isEmpty(void);
    void updateNumTenants(int);

    virtual bool save(void);
    virtual bool remove(void);

    static UnitModel *create(QString address,
                             const int num_rooms,
                             const int id);

    static bool exists(void);
    static QStringList *findAllAddrByUnitNumber(const int number);
    static QStringList *findAllUnitNoByAddress(QString address);

    QString toString(void);

    // data
    const int num_rooms;
    int num_members;
    const QString address;

protected:


    //static const char *column_names[20];
    static UnitModel *load(QSqlQuery &q, const int id);

private:
    UnitModel(QString streetAddress, const int nRooms,
              const int id, const int numMembers);
};

#endif // UNIT_H
