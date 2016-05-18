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
    bool _approved;

    static std::string _dbTable;
public:
    Loan(const Date creation, const Date validation, const User sender, const bool approved);
    Loan (const unsigned int id);

    unsigned int getId() const;

    void setCreation(Date creation);
    Date getCreation();

    void setValidation(Date validation);
    Date getValidation();

    bool getApproved();

    void validate();

    void decline();

    bool save();

    bool remove();
};

#endif //_LOAN_H
