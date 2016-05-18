/**
 * Project Untitled
 */


#ifndef _ADVISOR_H
#define _ADVISOR_H

#include "User.h"
#include "Administrator.h"
#include "Client.h"
class Client;
class Advisor: public User {

public:

    Advisor(int unsigned id); // Get a person from an ID provided by DB

    Advisor(const std::string lastName = "John", const std::string firstName = "Doe", const std::string password = "123");
    Advisor(const std::string lastName, const std::string firstName, const Date birthDate);
    bool isAdivsor();
    void ValidateLoan();
    void getUserBankAccounts();
    void CreateBankAccount();
    Client* getUsers();
    void TransferMoneyUser();
    void CloseBankAccount();

    void CreateClientAccount();
};

#endif //_ADVISOR_H
