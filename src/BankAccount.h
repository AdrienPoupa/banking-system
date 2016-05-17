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