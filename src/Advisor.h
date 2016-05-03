/**
 * Project Untitled
 */


#ifndef _ADVISOR_H
#define _ADVISOR_H

#include "User.h"
#include "Administrator.h"


class Advisor: public User {
public:

    void ValidateLoan();

    void CreateBankAccount();

    void CloseBankAccount();

    void CreateClientAccount();
};

#endif //_ADVISOR_H
