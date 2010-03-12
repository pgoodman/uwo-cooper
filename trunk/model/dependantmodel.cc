
#include "model/dependantmodel.h"

DependantModel::DependantModel(QString name, QDateTime bday)
{
	fullName = name;
	timeOf21stBday = bday;
}

bool DependantModel::isUnderAge(QDateTime currentTime)
{
	return (timeOf21stBday < currentTime);
}

DependantModel::~DependantModel() {
}
