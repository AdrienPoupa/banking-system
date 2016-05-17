/**
 * Project Untitled
 */


#include <set>
#include <iostream>
#include <map>
#include "Advisor.h"
#include "BaseModel.h"
#include "sha256.h"

using namespace std;

/**
 * Advisor implementation
 */

Advisor::Advisor(const unsigned int id) // Get a Advisor from an ID provided by DB
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if (!data.empty())
    {
        _id = id;
        _firstName = data["name"];
        _lastName = data["surname"];
        _birthDate = Date(data["birthdate"]);
        _phone = data["phone"];
        _address = Address(stoi(data["house_number"]), data["street"], data["postal_code"], data["town"], data["country"]);
        _isAdmin = stoi(data["isadmin"]);
        _password = data["password"];
    }
    else
    {
        throw invalid_argument("Please enter a valid ID");
    }
}
/*
Advisor::~Advisor()
{

}*/

Advisor::Advisor(const std::string lastName, const std::string firstName, const std::string password) {
    _lastName = lastName;
    _firstName = firstName;
    _password = sha256(password);
}

Advisor::Advisor(const std::string lastName, const std::string firstName, const Date birthDate){
    _lastName = lastName;
    _firstName = firstName;
    _birthDate = birthDate;

}


void Advisor::ValidateLoan() {

}

void Advisor::CreateBankAccount() {

}

void Advisor::CloseBankAccount() {

}

void Advisor::CreateClientAccount() {

}