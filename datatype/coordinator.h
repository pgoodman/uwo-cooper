
#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <QString>

#include <QSqlQuery>
#include <QVariant>

#include "conf.h"
#include "cooperdb.h"

#include "user.h"
#include "permission.h"

using namespace std;

class Coordinator : public User
{
public:
	static bool exists(void);
	static User *create(QString password);
	static User *load(void);
	static User *load(QString password);

	virtual QString getUserName(void);
	virtual void save(void);
	virtual bool hasPermission(const Permission p);
	virtual bool isSoftDeleted(void);
	virtual ~Coordinator();

private:
	explicit Coordinator(int, QString);

	static bool does_exist;
	static User *coord;
};

#endif // COORDINATOR_H
