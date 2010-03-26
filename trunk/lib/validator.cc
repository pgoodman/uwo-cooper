#include "validator.h"

Validator::Validator()
{
}

//check whether the input is a valid Canadian phone number.
//9 digits
bool Validator::isValidPhoneNo(QString inStr){
    bool ok;
    long long pno;
    if(inStr == "") {
        return false;
    } else {
        pno = inStr.toLongLong(&ok, 10);
        if(ok) {
            if(pno < PHONE_UP_EDGE && pno > PHONE_LOW_EDGE){
                return true;
            }else {
                return false;
            }
        }else {
            return ok;
        }
    }
}

//check whether the input is digit.
bool Validator::isValidDigit(QString inStr){
    bool ok;

    if(inStr == "") {
        return false;
    } else {
        inStr.toLong(&ok, 10);
        return ok;
    }

}
