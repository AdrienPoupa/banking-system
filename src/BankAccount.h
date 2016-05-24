/**
 * Project Untitled
 */


#ifndef _BANKACCOUNT_H
#define _BANKACCOUNT_H

#include <stdio.h>
#include <set>
#include <iostream>
#include "User.h"
#include "BaseModel.h"
#include "Client.h"

class BankAccount {
protected:
    unsigned int _id;
    std::string _swift;
    std::string _bic;
    int _balance;
    unsigned int _idUser;
    static std::string _dbTable;
public:
    BankAccount(unsigned int user_id, const std::string swift, const std::string bic, const int balance);
    BankAccount();
    BankAccount(std::string swift, std::string bic, int idUser);
    BankAccount(const int id);

    void setUserId(unsigned int user_id);
    unsigned int getUserId() const;

    unsigned int getId() const;
    void setBic(std::string bic);

    std::string getBic() const;
    void setSwift(std::string swift);

    std::string getSwift() const;
    bool save();

    int ConsultAmount();
    void decreaseAmount(int less);
    void setBalance(int balance);

    std::set<int> getExpenses();
    
    void Transfer(int amount, BankAccount* bc);

    std::string static random_string(size_t length);
    
    void ConsultHistory();

    void RequestSwift();

    friend std::ostream& operator<< (std::ostream& stream, const BankAccount& bankAccount);
};

#endif //_BANK ACCOUNT_H