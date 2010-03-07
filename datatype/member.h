#ifndef MEMBER_H
#define MEMBER_H

#include <istream>
#include <sstream>
#include <utility>
#include <time.h>
#include <string>
#include <vector>

#include <QString>
#include <QVariant>
#include <QSqlRecord>
#include <QDateTime>

#include "user.h"
#include "coordinator.h"
#include "dependant.h"
#include "committee.h"
#include "modeliterator.h"

using namespace std;

class Member : public User {

public:

    typedef class ModelIterator<Member, Member> iterator;

    //getters
    int getCommitteeID(void);
    int getUnit(void);
    double getMoneyOwed();

    bool isTelephoneShared();
    bool isMarkedDeleted();

    QString getTelephoneNum();
    QString getLoginName(void);
    QString getFirstName(void);
    QString getLastName(void);
    QString getPassword(void);
    QString getAddress(void);

    time_t getMoveInTime(void);
    Committee *getCommittee(void);

    virtual bool hasPermission(const Permission p);
    virtual bool isSoftDeleted(void);

    virtual QString getUserName(void);
    virtual QString toString();

    //setters
    void setTelephoneNumber(QString newNumber);
    void setMoneyOwed(double money);
    void setSharedTelephone(bool share);
    void setMarked(bool mark);
    void setFirstName(QString firstName);
    void setLastName(QString lastName);
    void setUnit(int unitNo);
    void setAddress(QString addr);
    void setLoginName(QString loginName);
    void setPassword(QString pwd);
    void setMoveInTime(QDateTime mvTime);
    void setCommitteeID(int committeeID);

    virtual void setFullName(QString firstName, QString lastName);
    virtual void softDelete(bool);

    //actions
    virtual void hardDelete(void);
    virtual void save(void);

    static Member *load(const int id);
    static Member *load(QString &uname, QString &pass);
    static Member *create(QString firstName, QString lastName,
                          QString telephone,
                          const bool share_telephone, QString user_name,
                          QString password, const time_t move_in_time, int unit_no,
                          QString unit_addr, const int committee_id);

    static pair<iterator, iterator> findAll();

private:

    static Member *load(QSqlQuery &q, const bool checked_id=true);

    QString telephone_num;
    double money_owed;
    bool share_telephone;
    bool is_marked;
    int committee_id;
    QString user_name;
    QString first_name;
    QString last_name;
    time_t move_in_time;
    Committee *committee;
    int unit;
    QString address;

    explicit Member(QString firstName, QString lastName, double newMoneyOwed,
                    QString phoneNum, bool sharePhone, bool mark,
                    QString userName, QString password, int committeeId,
                    int id);
};


#endif // MEMBER_H
