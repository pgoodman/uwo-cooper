#ifndef USER_H
#define USER_H

#include <string>
#include <map>

#include <QSqlQuery>

#include "permission.h"
#include "cooperdb.h"
//#include "model.h"

using namespace std;

class User {
public:
    //Constructors
    User();
    User(string newName, string newUserName, string newPassword, int newID);
    
    virtual string getFullName();
    virtual string getUserName() = 0;
    virtual void save(void) = 0;
    virtual bool hasPermission(const Permission p) = 0;
    virtual bool remove(void);

    bool hasPassword(string &pass);
    int getID();

    //Modifiers
    virtual void setFullName(string fullName);
    /*void setName(string newName);
    void setUserName(string newUserName);
    void setPassword(string newPassword);
    void setID(int newID);*/

    virtual ~User() { }

protected:

    static void remember(const int id, User *val);
    static User *recall(const int id);
    static bool remembered(const int id);

	//Attributes

	string full_name;
	string password;
	int id;

	static map<int, User *> elms;
};

#endif // USER_H
