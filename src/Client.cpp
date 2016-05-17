/**
 * Project Untitled
 */


#include <set>
#include <iostream>
#include <map>
#include "Client.h"
#include "BaseModel.h"
#include "sha256.h"

using namespace std;

/**
 * Client implementation
 */

Client::Client(const unsigned int id) // Get a Client from an ID provided by DB
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
        throw invalid_argument("Merci d'entrer un utilisateur valide");
    }
}
/*
Client::~Client()
{

}*/

Client::Client(const std::string lastName, const std::string firstName, const std::string password) {
    _lastName = lastName;
    _firstName = firstName;
    _password = sha256(password);
}

Client::Client(const std::string lastName, const std::string firstName, const Date birthDate){
    _lastName = lastName;
    _firstName = firstName;
    _birthDate = birthDate;

}


void Client::ContactAdvisor() {

}

void Client::LoanApplication() {

}