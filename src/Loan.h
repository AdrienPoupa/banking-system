/**
 * Project Untitled
 */


#ifndef _LOAN_H
#define _LOAN_H

#include "Date.h"
#include "User.h"

class Loan {
public:
    Date creation;
    Date validation;
    User sender;

    void validate();

    void decline();
};

#endif //_LOAN_H
