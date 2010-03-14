/*
 * member_committee.h
 *
 *  Created on: Mar 12, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef MEMBER_COMMITTEE_H_
#define MEMBER_COMMITTEE_H_

#include <sstream>
#include <string>

#include <QDateTime>
#include <QString>
#include <QSqlQuery>
#include <QTextStream>

#include "lib/database.h"
#include "lib/imodel.h"

#include "model/permissionmodel.h"
#include "model/usermodel.h"
#include "model/dependantmodel.h"
#include "model/unitmodel.h"
#include "model/taskmodel.h"

using namespace std;

class MemberModel;
class CommitteeModel;

/**
 * Member model.
 */
class MemberModel : public UserModel,
                    public IModel<MemberModel,select_from_table_tag> {
    MODEL_CLASS(MemberModel);

public:
    static const char *table_name;

    //getters
    UnitModel *getUnit(void);
    double getMoneyOwed();

    bool isTelephoneShared();
    bool isMarkedDeleted();
    bool wasAssignedCommittee(void);

    QString getTelephoneNum();
    QString getLoginName(void);
    QString getFirstName(void);
    QString getLastName(void);
    QString getAddress(void);
    QString getUnitNo(void);

    QDateTime getMoveInTime(void);
    CommitteeModel *findCommittee(void);

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

    virtual bool save(void);
    virtual bool hasPermission(const PermissionModelSet p);
    virtual bool remove(void);

    virtual QString getUserName(void);
    virtual QString toString();

    static MemberModel *findByLoginInfo(QString uname, QString pass);
    static MemberModel *create(const bool sharePhone,
                          QDateTime moveInTime,
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
    static iterator_range findAll(const char *);

    virtual ~MemberModel();

protected:
    static MemberModel *load(QSqlQuery &q, const int id);

private:

    int committee_id;
    int unit_id;
    bool share_telephone;
    bool is_marked;
    bool had_committee;
    double money_owed;
    QDateTime move_in_time;
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
                         const bool hadCommittee,
                         const double moneyOwed,
                         QDateTime moveInTime,
                         QString phoneNum,
                         QString userName,
                         QString firstName,
                         QString lastName,
                         QString addr,
                         QString pass);
};

/**
 * Committee Model.
 */
class CommitteeModel : public IModel<CommitteeModel, select_from_table_tag> {

    MODEL_CLASS(CommitteeModel);

public:
    static const char *table_name;

    virtual bool save(void);

    static bool create(QString n, const bool canDelete,
                const PermissionModelSet chairPerms,
                const PermissionModelSet memberPerms,
                const int chairId, const int secretaryId);

    bool addTask(QString name, QString description, QDateTime deadline) const;
    bool canRemove(void) const;
    virtual bool remove(void);

    TaskModel::iterator_range findTasks(void);

    PermissionModelSet getPermissions(const int member_id);
    QString toString(void);

    virtual ~CommitteeModel();

    static const int BOARD_COMMITTEE_ID = 1;
    static const int INSPECTIONS_COMMITTEE_ID = 2;
    static const int MEMBERSHIP_COMMITTEE_ID = 3;
    static const int EDUCATION_COMMITTEE_ID = 4;
    static const int MEMBER_RELATIONS_COMMITTEE_ID = 5;

protected:

    static CommitteeModel *load(QSqlQuery &q, const int id);

private:
    explicit CommitteeModel(QString n, const bool canDelete,
                            const PermissionModelSet chairPerms,
                            const PermissionModelSet memberPerms,
                            const int chair_id, const int secretary_id,
                            const int committeeId);

    QString name;
    bool can_delete;

    MemberModel *chair;
    MemberModel *secretary;

    PermissionModelSet chair_perms;
    PermissionModelSet member_perms;

    int chair_id;
    int secretary_id;
};

#endif /* MEMBER_COMMITTEE_H_ */
