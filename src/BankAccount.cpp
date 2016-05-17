/**
 * Project Untitled
 */


#include "BankAccount.h"
#include <iostream>

using namespace std;
/**
 * BankAccount implementation
 */
string BankAccount::_dbTable = "bank_account";

BankAccount::BankAccount(){

}
BankAccount::BankAccount(std::string swift, std::string bic, int idUser){
    _swift = swift;
    _bic = bic;
    try {
        User *user = new User(idUser);
    }
    catch (exception e){
        cout << e.what()<<endl;
    }
    _idUser=idUser;
}

BankAccount::BankAccount(const int id) // Get a User from an ID provided by DB
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if (!data.empty()) {
        _id = id;
        _swift = data["swift"];
        _bic = data["bic"];
        _balance = stoi(data["balance"]);
        _idUser = stoi(data["id_user"]);
    }
    else {
        throw invalid_argument("The id of the bank account does not exist.");
    }
}

void BankAccount::ConsultAmount() {

}

void BankAccount::Transfer() {

}

void BankAccount::ConsultHistory() {

}

void BankAccount::RequestSwift() {

}

int BankAccount::getId() const{
    return this->_id;
}

int BankAccount::getBalance() const{
    return this->_balance;
}

ostream& operator<< (ostream& stream, const BankAccount& bankAccount)
{
    User* user = new User(bankAccount._idUser);
    stream << "Bank account n°: "<< bankAccount.getId()<<endl;
    stream << "Owner: " << user->getFirstName() << " " << user->getLastName() << endl;
    stream << "Balance: " << bankAccount._balance << endl;
    /*stream << "Anniversaire: " << user._birthDate << endl;
    stream << "Telephone: " << user._phone << endl;
    stream << "Adresse: " << user._address << endl;
    stream << "Est admin: " << isAdmin << endl;*/

    return stream;
}