/**
 * Project Untitled
 */


#include "BankAccount.h"
using namespace std;
/**
 * BankAccount implementation
 */

string BankAccount::_dbTable = "bank_account";

BankAccount::BankAccount(unsigned int user_id, const string swift, const string bic) :_idUser(user_id),
                                                                                         _swift(swift),
                                                                                         _bic(bic) { }

unsigned int BankAccount::getId() const{
    return _id;
}

void BankAccount::setUserId(unsigned int user_id) {
    _idUser = user_id;
}

unsigned int BankAccount::getUserId() const {
    return _idUser;
}

void BankAccount::setBic(std::string bic) {
    _bic = bic;
}

std::string BankAccount::getBic() const {
    return _bic;
}

void BankAccount::setSwift(std::string swift) {
    _swift = swift;
}

std::string BankAccount::getSwift() const {
    return _swift;
}
BankAccount::BankAccount(){

}
BankAccount::BankAccount(std::string swift, std::string bic, int idUser){
    _swift = swift;
    _bic = bic;
    try {
        User *user = new Client(idUser);
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
        _swift = data["SWIFT"];
        _bic = data["BIC"];
        _balance = stoi(data["balance"]);
        _idUser = stoi(data["id_user"]);
    }
    else {
        throw invalid_argument("The id of the bank account does not exist.");
    }
}

int BankAccount::ConsultAmount() {
    return this->_balance;
}
bool BankAccount::save(){
        int res = BaseModel::save(_dbTable, {
                {"id", {to_string(_id), "int"}},
                {"SWIFT", {_swift,"string"}},
                {"BIC", {_bic, "string"}},
                {"balance", {to_string(_balance), "int"}},
                {"id_user", {to_string(_idUser), "int"}},
        });
        if (_id == 0)
        {
            _id = res["id"];
        }

        return (bool) res;
}
void BankAccount::Transfer(int amount, BankAccount* bc) {
    this->_balance -= amount;
    this->save();
    bc->_balance += amount;
    bc->save();
}

void BankAccount::ConsultHistory() {

}

void BankAccount::RequestSwift() {

}


ostream& operator<< (ostream& stream, const BankAccount& bankAccount)
{
    User* user = new Client(bankAccount._idUser);
    stream << "Bank account n°: "<< bankAccount.getId()<<endl;
    stream << "Owner: " << user->getFirstName() << " " << user->getLastName() << endl;
    stream << "Balance: " << bankAccount._balance << endl;
    /*stream << "Anniversaire: " << user._birthDate << endl;
    stream << "Telephone: " << user._phone << endl;
    stream << "Adresse: " << user._address << endl;
    stream << "Est admin: " << isAdmin << endl;*/

    return stream;
}