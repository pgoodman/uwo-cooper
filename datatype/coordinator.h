
#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <string>

#include <QSqlQuery>
#include <QVariant>

#include "conf.h"
#include "cooperdb.h"
#include "datatype/user.h"

using namespace std;

class Coordinator : public User
{
public:
	static bool exists(void);
	static void create(string full_name, string password);
	static User *load(void);

	virtual string getUserName(void);
	virtual ~Coordinator();

private:
	Coordinator(int, string, string);

	static bool does_exist;
	static User *coord;
};

#endif // COORDINATOR_H
