#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <string>
#include "datatype/user.h"

using namespace std;

class Coordinator : public User
{
public:
	Coordinator();

protected:
	string name;
};

#endif // COORDINATOR_H
