/**
 * Project Untitled
 */


#ifndef _CLIENT_H
#define _CLIENT_H

#include "User.h"
#include "Advisor.h"
#include "Contact.h"
#include "BankAccount.h"
class BankAccount;

class Client: public User {
public:

    Client(int unsigned id); // Get a person from an ID provided by DB

    Client(const std::string lastName = "John", const std::string firstName = "Doe", const std::string password = "123");
    Client(const std::string lastName, const std::string firstName, const Date birthDate);

    BankAccount* getBankAccounts();
    void contactAdvisor();
    void Transfer();
    void LoanApplication();
};

#endif //_CLIENT_H
