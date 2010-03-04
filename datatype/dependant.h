#ifndef DEPENDANT_H
#define DEPENDANT_H

#include <QString>
#include <time.h>

using namespace std;


class Dependant
{
public:
	//Constructors
	Dependant();
	Dependant(QString name, time_t bday);
	~Dependant();	

	//methods
	bool isUnderAge(time_t currentTime);

	//accessor methods
	QString getName(){return fullName;}
	time_t getBday(){return timeOf21stBday;}

private:
	QString fullName;
	time_t timeOf21stBday;
};

#endif // DEPENDANT_H
