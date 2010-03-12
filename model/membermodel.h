#ifndef MEMBER_H
#define MEMBER_H

#include <sstream>
#include <string>
#include <time.h>

#include <QString>
#include <QVariant>
#include <QSqlRecord>
#include <QDateTime>

#include "model/usermodel.h"
#include "model/dependantmodel.h"
#include "model/committeemodel.h"
#include "model/unitmodel.h"

using namespace std;

class MemberModel : public UserModel,
                    public IModel<MemberModel,select_from_table_tag> {
    MODEL_CLASS(MemberModel);

public:
    static const char *table_name;

    //getters
    int getCommitteeId(void);
    UnitModel *getUnit(void);
    double getMoneyOwed();

    bool isTelephoneShared();
    bool isMarkedDeleted();

    QString getTelephoneNum();
    QString getLoginName(void);
    QString getFirstName(void);
    QString getLastName(void);
    QString getAddress(void);

    time_t getMoveInTime(void);
    CommitteeModel *getCommittee(void);

    //setters
    void markDeleted(bool mark);
    void setTelephoneNumber(QString newNumber);
    void setMoneyOwed(double money);
    void setSharedTelephone(bool share);
    void setFirstName(QString firstName);
    void setLastName(QString lastName);
    void setUnit(UnitModel *unit);
    void setAddress(QString addr);
    void setLoginName(QString loginName);
    void setMoveInTime(QDateTime mvTime);
    void setCommittee(CommitteeModel *committee);
    void setFullName(QString firstName, QString lastName);

    virtual void save(void);
    virtual bool hasPermission(const PermissionModel p);
    virtual void remove(void);

    virtual QString getUserName(void);
    virtual QString toString();

    static MemberModel *findByLoginInfo(QString uname, QString pass);
    static MemberModel *create(const bool sharePhone,
                          const time_t moveInTime,
                          QString phoneNum,
                          QString userName,
                          QString firstName,
                          QString lastName,
                          QString addr,
                          QString pass,
                          CommitteeModel *committee,
                          UnitModel *unit);
    static MemberModel *createIncomplete(QString lastName, UnitModel *unit);
    static iterator_range findAll();
    
    virtual ~MemberModel();

protected:
    static MemberModel *load(QSqlQuery &q, const int id);

private:

    int committee_id;
    int unit_id;
    bool share_telephone;
    bool is_marked;
    double money_owed;
    time_t move_in_time;
    QString telephone_num;
    QString user_name;
    QString first_name;
    QString last_name;
    QString address;

    // lazy loaded
    CommitteeModel *committee;
    UnitModel *unit;

    explicit MemberModel(const int id,
                         const int committeeId,
                         const int unitId,
                         const bool sharePhone,
                         const bool isMarked,
                         const double moneyOwed,
                         const time_t moveInTime,
                         QString phoneNum,
                         QString userName,
                         QString firstName,
                         QString lastName,
                         QString addr,
                         QString pass);
};

#endif // MEMBER_H
