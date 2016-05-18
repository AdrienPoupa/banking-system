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
        _isAdvisor = stoi(data["isadvisor"]);
        _password = data["password"];
    }
    else
    {
        throw invalid_argument("Please enter a valid ID");
    }
}
/*
Client::~Client()
{

}*/
BankAccount* Client::getBankAccounts() {
    map<int, map<string, string>> bankAccount = BaseModel::select("bank_account", "id, swift, BIC,id_user,balance");

    int totalAccount = (int)bankAccount.size();

    int idToOpen;
    set<int> AccountIds = set<int>();
    bool correctId = false;

    do{
        string swiftspace;
        string bicSpace;
        string idSpace;
        cout << "-------------------------------------------------------" << endl;
        cout << " -- Account's list of "<< getLastName() << " " << getFirstName() <<" --" << endl;
        cout << " ID |       SWIFT       |     BIC     " << endl;
        cout << "----|-------------------|--------------" << endl;
        for (int i = 1; i != totalAccount + 1; i++)
        {
            if(stoi(bankAccount[i]["id_user"]) == getId()) {
                cout << bankAccount[i]["id"] << "     " << bankAccount[i]["SWIFT"] << "          " <<
                bankAccount[i]["BIC"] << endl;
                AccountIds.insert(stoi(bankAccount[i]["id"]));
            }
        }

        cout << endl << "Bank account's id : " << endl;
        cin >> idToOpen;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            correctId = AccountIds.find(idToOpen) != AccountIds.end();
        }

        if (!correctId)
        {
            cout << "Identifiant inconnu ..." << endl;
        }

    } while(!correctId);
    BankAccount *bc = new BankAccount(idToOpen);
    cout << *bc<<endl;
    return bc;
}
Client::Client(const std::string lastName, const std::string firstName, const std::string password) {
    _lastName = lastName;
    _firstName = firstName;
    _password = sha256(password);
}

void Client::Transfer(){
    int amountToTransfer;
    BankAccount* bc = getBankAccounts();
    cout << endl << "Amount to transfer : " << endl;
    cin >> amountToTransfer;

    if(bc->getBalance() < amountToTransfer){
        cout << "Insufficient amount" << endl;
    }
    else{

    }
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