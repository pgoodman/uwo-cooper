#ifndef VALIDATOR_H
#define VALIDATOR_H

#define PHONE_UP_EDGE 999999999
#define PHONE_LOW_EDGE 100000000

#include <QString>

class Validator
{
public:
    Validator();
    static bool isValidPhoneNo(QString inStr);
    static bool isValidDigit(QString inStr);

};

#endif // VALIDATOR_H
