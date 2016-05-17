/**
 * Project Untitled
 */


#ifndef _LOAN_H
#define _LOAN_H

#include "Date.h"
#include "User.h"

class Loan {
protected:
    unsigned int _id;
    Date _creation;
    Date _validation;
    User _sender;
public:
    Loan(const Date creation, const Date validation, const User sender);

    // todo: Loan from ID

    unsigned int getId() const;

    void setCreation(Date creation);
    Date getCreation();

    void setValidation(Date validation);
    Date getValidation();

    void validate();

    void decline();

    // todo: DB
};

#endif //_LOAN_H
