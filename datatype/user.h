#ifndef USER_H
#define USER_H

#include <QString>
#include <map>
#include <iostream>

#include <QSqlQuery>

#include "cooperdb.h"
#include "datatype/permission.h"

using namespace std;

class User {
public:

    virtual QString getUserName() = 0;
    virtual void save(void) = 0;
    virtual bool hasPermission(const Permission p) = 0;
    virtual void softDelete(bool);
    virtual void hardDelete(void);
    virtual bool isSoftDeleted(void) = 0;

    bool hasPassword(QString &pass);
    int getID();

    virtual ~User() { }

    static void setActive(User *);
    static bool canDo(Permission); // can't re-declare hasPermission :/
    static bool nameExists(QString userName);

protected:


    explicit User(const int userId, const bool isCoordinator, QString pwd);

    static void remember(const int id, User *val);
    static User *recall(const int id);
    static bool remembered(const int id);

    const int id;
	bool is_coordinator;
	QString password;

	static map<int, User *> elms;

private:
	static User *active;
};

#endif // USER_H
