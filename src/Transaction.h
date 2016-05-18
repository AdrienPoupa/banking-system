//
// Created by Adrien on 17/05/2016.
//

#ifndef BANKING_SYSTEM_TRANSACTION_H
#define BANKING_SYSTEM_TRANSACTION_H


#include "BankAccount.h"
#include "Date.h"

class Transaction {
protected:
    unsigned int _id;
    BankAccount _account;
    Date _date;
    int _amount;
    std::string _description;

    static std::string _dbTable;
public:
    Transaction(const BankAccount account, const Date date, int amount, const std::string description);
    Transaction (const unsigned int id);

    unsigned int getId() const;

    void setBankAccount(BankAccount account);
    BankAccount getBankAccount();

    void setDate(Date date);
    Date getDate();

    void setAmount(int amount);
    int getAmount();

    void setDescription(std::string description);
    std::string getDescription();

    bool save();

    bool remove();
};


#endif //BANKING_SYSTEM_TRANSACTION_H
