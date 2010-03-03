#ifndef DEPENDANT_H
#define DEPENDANT_H

#include <string>
#include <time.h>

using namespace std;


class Dependant
{
public:
	//Constructors
	Dependant();
	Dependant(string name, time_t bday);
	~Dependant();	

	//methods
	bool isUnderAge(time_t currentTime);

	//accessor methods
	string getName(){return fullName;}
	time_t getBday(){return timeOf21stBday;}

private:
	string fullName;
	time_t timeOf21stBday;
};

#endif // DEPENDANT_H
