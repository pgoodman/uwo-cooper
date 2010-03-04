#ifndef MEMBER_H
#define MEMBER_H

#include <istream>
#include <sstream>
#include <string>
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

	//Member methods
    /*
	bool owesMoney();
	bool isMovedIn();
	void addDependant(Dependant dependant);	

	//Acessor methods
	string getTelephoneNumber() {return telephoneNumber;}
	double getMoneyOwed() {return moneyOwed;}
	bool   sharesTelephone() {return shareTelephone;}
	bool   checkMarked() {return isMarked;}
	string fullName() {return full_name;}
	string getUserName(void);

	//Modifiers
	*/
	void setTelephoneNumber(string newNumber);
	void setMoneyOwed(double money);
	void setSharedTelephone(bool share);
	void setMarked(bool mark);


    typedef class ModelIterator<User, Member> iterator;

	virtual void save(void);
	virtual bool hasPermission(const Permission p);
	virtual string getUserName(void);

	static User *load(const int id);
    static User *load(string &uname, string &pass);

    static User *create(string full_name, string telephone,
                        const bool share_telephone, string user_name,
                        string password, const time_t move_in_time);

    static pair<iterator, iterator> findAll();

private:

    static User *load(QSqlQuery &q, const bool checked_id=true);

	string telephone_num;
	double money_owed;
	bool share_telephone;
	bool is_marked;
	bool has_committee;
	string user_name;
	time_t move_in_time;
	Committee *committee;

    Member(string fullName, double newMoneyOwed,
           string phoneNum, bool sharePhone, bool mark, string userName,
           string password, bool has_committee, int id);
};

#endif // MEMBER_H
