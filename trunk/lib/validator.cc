
#include "validator.h"

const quint64 Validator::PHONE_UP_EDGE = Q_UINT64_C(9999999999);
const quint64 Validator::PHONE_LOW_EDGE = Q_UINT64_C(1000000000);

Validator::Validator() { }

/**
 * Check whether the input is a valid Canadian phone number.
 */
bool Validator::isValidPhoneNo(QString inStr){
    bool ok;
    quint64 pno;
    if(inStr == "") {
        return false;
    } else {
        pno = inStr.toULongLong(&ok, 10);
        return ok && pno < PHONE_UP_EDGE && pno > PHONE_LOW_EDGE;
    }
}

/*
 * Check whether the input is digit.
 */
bool Validator::isValidDigit(QString inStr){
    if(inStr == "") {
        return false;
    }

    bool ok;
    inStr.toLong(&ok, 10);
    return ok;
}
