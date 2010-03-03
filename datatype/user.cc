#include <string>
#include "user.h"

using namespace std;

User::User()
{
}

User::User(string newName, string newUserName, string newPassword, int newID)
{
	name = newName;
	userName = newUserName;
	password = newPassword;
	id = newID;
}
