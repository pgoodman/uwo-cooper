#ifndef DEPENDANT_H
#define DEPENDANT_H

#include <QString>
#include <QDateTime>

using namespace std;

class DependantModel
{
public:
    //Constructors
    DependantModel(QString name, QDateTime bday);
    ~DependantModel();

    //methods
    bool isUnderAge(QDateTime currentTime);

    //accessor methods
    QString getName(){return fullName;}
    QDateTime getBday(){return timeOf21stBday;}

private:
    QString fullName;
    QDateTime timeOf21stBday;
};

#endif // DEPENDANT_H
