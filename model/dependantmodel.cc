
#include "model/dependantmodel.h"

DependantModel::DependantModel(QString name, time_t bday)
{
	fullName = name;
	timeOf21stBday = bday;
}

bool DependantModel::isUnderAge(time_t currentTime)
{
	return (timeOf21stBday < currentTime);
}

DependantModel::~DependantModel() {
}
