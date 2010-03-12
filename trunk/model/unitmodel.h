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
    virtual void save(void);

    static UnitModel *create(QString address,
                             const int num_rooms,
                             const int id);

    static bool exists(void);

    QString toString(void);

    // data
    const int num_rooms;
    const int num_members;
    const QString address;

protected:


    //static const char *column_names[20];
    static UnitModel *load(QSqlQuery &q, const int id);

private:
    UnitModel(QString streetAddress, const int nRooms,
              const int id, const int numMembers);
};

#endif // UNIT_H
