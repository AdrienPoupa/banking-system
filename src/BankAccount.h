/**
 * Project Untitled
 */


#ifndef _BANKACCOUNT_H
#define _BANKACCOUNT_H

#include <stdio.h>
#include <set>
#include <iostream>

class BankAccount {
protected:
    unsigned int _id;
    unsigned int _user_id;
    std::string _swift;
    std::string _bic;
public:
    BankAccount(unsigned int user_id, const std::string swift, const std::string bic);

    // todo: BankAccount from ID

    void setUserId(unsigned int user_id);
    unsigned int getUserId();

    unsigned int getId();

    void setBic(std::string bic);
    std::string getBic();

    void setSwift(std::string swift);
    std::string getSwift();

    void ConsultAmount();
    
    void Transfer();
    
    void ConsultHistory();
    
    void RequestSwift();

    // todo: DB
};

#endif //_BANK ACCOUNT_H