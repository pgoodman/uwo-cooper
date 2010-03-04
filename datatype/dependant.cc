#include "dependant.h"
#include <time.h>

Dependant::Dependant()
{
}

Dependant::Dependant(QString name, time_t bday)
{
	fullName = name;
	timeOf21stBday = bday;
}

bool Dependant::isUnderAge(time_t currentTime)
{
	return (timeOf21stBday < currentTime);
}

Dependant::~Dependant() {
}
