#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
public:
    //Constructors
    User();
    User(string name, string userName, string password, int id);
    
    //Accessors
    string getName() {return name;}
    string getUserName() {return userName;}
    string getPassword() {return password;}
    int getID() {return id;}

protected:
	//Attributes
	string name;
	string userName;
	string password;
	int id;
};

#endif // USER_H
