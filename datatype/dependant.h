#ifndef DEPENDANT_H
#define DEPENDANT_H

#include <string>

using namespace std;


class Dependant
{
public:
	//Constructors
	Dependant();
	Dependant(string name, time_t bday);

	//methods
	bool isUnderAge();

	//accessor methods
	string getName(){return name;}
	time_t getBday(){return timeOf21stBirthday;}

private:
	string name;
	time_t timeOf21stBirthday;
};

#endif // DEPENDANT_H
