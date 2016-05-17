/**
 * Project Untitled
 */
#include <iostream>
#include "user.h"
#include "BaseModel.h"

#ifndef _BANKACCOUNT_H
#define _BANKACCOUNT_H

class BankAccount {
private:
    unsigned int _id;
    std::string _swift;
    std::string _bic;
    int _balance;
    int _idUser;
    static std::string _dbTable;
public:
    BankAccount();
   BankAccount(std::string swift, std::string bic, int idUser);
   BankAccount(const int id);
    int getId() const;
    int getBalance() const;

    void ConsultAmount();
    
    void Transfer();
    
    void ConsultHistory();
    
    void RequestSwift();
    friend std::ostream& operator<< (std::ostream& stream, const BankAccount& bankAccount);
};

#endif //_BANK ACCOUNT_H