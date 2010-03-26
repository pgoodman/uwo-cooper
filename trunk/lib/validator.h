#ifndef VALIDATOR_H
#define VALIDATOR_H

#define PHONE_UP_EDGE 9999999999
#define PHONE_LOW_EDGE 1000000000

#include <QString>

class Validator
{
public:
    Validator();
    static bool isValidPhoneNo(QString inStr);
    static bool isValidDigit(QString inStr);

private:
    int phone_up_edge;
    int phone_low_edge;

};

#endif // VALIDATOR_H
