#ifndef MEMBER_H
#define MEMBER_H

#include <istream>
#include <sstream>
#include <QString>
#include <utility>
#include <time.h>
#include <vector>

#include <QVariant>
#include <QSqlRecord>

#include "user.h"
#include "coordinator.h"
#include "dependant.h"
#include "committee.h"
#include "modeliterator.h"

using namespace std;

class Member : public User {

public:

	void setTelephoneNumber(QString newNumber);
	void setMoneyOwed(double money);
	void setSharedTelephone(bool share);
	void setMarked(bool mark);
	virtual QString getFullName();
    virtual void setFullName(QString fullName);


    typedef class ModelIterator<Member, Member> iterator;

	virtual void save(void);
	virtual bool hasPermission(const Permission p);
	virtual QString getUserName(void);

	static Member *load(const int id);
    static Member *load(QString &uname, QString &pass);

    static Member *create(QString full_name, QString telephone,
                        const bool share_telephone, QString user_name,
                        QString password, const time_t move_in_time);

    static pair<iterator, iterator> findAll();

private:

    static Member *load(QSqlQuery &q, const bool checked_id=true);

	QString telephone_num;
	double money_owed;
	bool share_telephone;
	bool is_marked;
	int committee_id;
	QString user_name;
	QString full_name;
	time_t move_in_time;
	Committee *committee;

    Member(QString fullName, double newMoneyOwed,
           QString phoneNum, bool sharePhone, bool mark, QString userName,
           QString password, int committeeId, int id);
};

#endif // MEMBER_H
