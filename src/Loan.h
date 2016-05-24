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
    int _amount;
    bool _approved;
    int _advisorId;

    static std::string _dbTable;
public:
    Loan(const Date creation, const Date validation, const User sender, const bool approved, const int amount, const int _advisorId);
    Loan (const unsigned int id);
    Loan();

    unsigned int getId() const;

    void setCreation(Date creation);
    Date getCreation();

    void setValidation(Date validation);
    Date getValidation();

    void setAmount(int amount);
    int getAmount();

    void setSender(User sender);
    User getSender();

    void setAdvisor(int advisorId);
    int getAdvisor();

    bool getApproved();

    void validate();

    void decline();

    bool save();

    bool remove();

    friend std::ostream& operator<< (std::ostream& stream, const Loan& loan);
    friend std::istream& operator>> (std::istream& stream, Loan& loan);
};

#endif //_LOAN_H
