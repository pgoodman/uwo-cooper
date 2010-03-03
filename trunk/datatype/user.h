#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User
{
public:
    //Constructors
    User();
    User(string newName, string newUserName, string newPassword, int newID);
    
    string getName();
    virtual string getUserName() = 0;

    string getPassword();
    int getID();

    //Modifiers
    /*void setName(string newName);
    void setUserName(string newUserName);
    void setPassword(string newPassword);
    void setID(int newID);*/

    // get a user from the database
    static User *load(const unsigned int id=0);
    static User *load(string &uname, string &pass);

protected:
	//Attributes
	string full_name;
	string password;
	int id;

	static vector<User *> users;
};

#endif // USER_H
