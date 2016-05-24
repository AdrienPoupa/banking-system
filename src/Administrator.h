/**
 * Banking system
 */


#ifndef _ADMINISTRATOR_H
#define _ADMINISTRATOR_H

#include "User.h"
#include "Advisor.h"
#include "User.h"


class Administrator: public User{
public:

    Administrator(int unsigned id); // Get a person from an ID provided by DB

    Administrator(const std::string lastName = "John", const std::string firstName = "Doe", const std::string password = "123");
    Administrator(const std::string lastName, const std::string firstName, const Date birthDate);

    void CreateAdvisorAccount();
};

#endif //_ADMINISTRATOR_H
