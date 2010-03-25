#include "validator.h"

Validator::Validator()
{
}

//check whether the input is a valid Canadian phone number.
bool Validator::isValidPhoneNo(QString inStr){
    bool ok;
    long pno;
    if(inStr == "") {
        return false;
    } else {
        pno = inStr.toLong(&ok, 10);
        if(ok) {
              return(pno > PHONE_UP_EDGE || pno < PHONE_LOW_EDGE);
        }else {
            return ok;
        }
    }
}

bool Validator::isValidDigit(QString inStr){
    bool ok;

    if(inStr == "") {
        return false;
    } else {
        inStr.toLong(&ok, 10);
        return ok;
    }

}
