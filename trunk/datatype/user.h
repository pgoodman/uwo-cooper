#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

#include <QSqlQuery>

#include "permission.h"

using namespace std;

class User
{
public:
    //Constructors
    User();
    User(string newName, string newUserName, string newPassword, int newID);
    
    string getName();
    virtual string getUserName() = 0;
    virtual void save(void) = 0;
    virtual bool hasPermission(const Permission p) = 0;

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

	//Attributes

	string full_name;
	string password;
	int id;

	static vector<User *> users;
};

#endif // USER_H
