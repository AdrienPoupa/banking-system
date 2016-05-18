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
        _isAdvisor = stoi(data["isadmin"]);
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

void Advisor::getUserBankAccounts() {
    map<int, map<string, string>> users = BaseModel::select("users", "id, name, surname, isadmin, isadvisor");

    int totalUsers = (int)users.size();

    unsigned int idToOpen;
    set<int> userIds = set<int>();
    bool correctId = false;
    do{
        cout << "-------------------------------------------------------" << endl;
        cout << " -- Client's list --" << endl;
        cout << " Identifiant | Prenom Nom " << endl;
        cout << "-------------|-------------------" << endl;
        for (int i = 1; i != totalUsers + 1; i++)
        {
            string space, star = "";

            for(unsigned int i = 0; i < (11 - users[i]["id"].length()); i++){
                space += " ";
            }

            if (users[i]["isadmin"] == "1") {
                star = "* ";
            }
            if(users[i]["isadmin"] != "1" && users[i]["isadvisor"] != "1") {
                cout << space << users[i]["id"] << " | " << star << users[i]["name"] << " " << users[i]["surname"] <<
                endl;
                userIds.insert(stoi(users[i]["id"]));
            }
        }

        cout << endl << "Client's id : " << endl;
        cin >> idToOpen;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            correctId = userIds.find(idToOpen) != userIds.end();
        }

        if (!correctId)
        {
            cout << "Identifiant inconnu ..." << endl;
        }

    } while(!correctId);

    Client *client = new Client(idToOpen);
    client->getBankAccounts();
}

void Advisor::ValidateLoan() {

}

void Advisor::CreateBankAccount() {

}

void Advisor::CloseBankAccount() {

}

void Advisor::CreateClientAccount() {

}