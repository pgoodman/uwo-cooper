#ifndef USER_H
#define USER_H

#include <QString>
#include <map>
#include <iostream>

#include <QSqlQuery>

#include "permission.h"
#include "cooperdb.h"
//#include "model.h"

using namespace std;

class User {
public:
    User();
    User(QString newName, QString newUserName, QString newPassword, int newID);
    

    virtual QString getUserName() = 0;
    virtual void save(void) = 0;
    virtual bool hasPermission(const Permission p) = 0;
    virtual bool remove(void);

    bool hasPassword(QString &pass);
    int getID();

    virtual ~User() { }

protected:

    static void remember(const int id, User *val);
    static User *recall(const int id);
    static bool remembered(const int id);

	//Attributes


	QString password;
	int id;

	static map<int, User *> elms;
};

#endif // USER_H
