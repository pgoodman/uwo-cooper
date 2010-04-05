#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QtGlobal>
#include <QString>

/**
 * Validate input according to some patterns.
 */
class Validator
{
public:
    static bool isValidPhoneNo(QString inStr);
    static bool isValidDigit(QString inStr);

private:
    Validator();
    static const quint64 PHONE_UP_EDGE;
    static const quint64 PHONE_LOW_EDGE;

};

#endif // VALIDATOR_H
