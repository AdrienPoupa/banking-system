/**
 * Project Untitled
 */


#include "BankAccount.h"
#include "Transaction.h"

using namespace std;
/**
 * BankAccount implementation
 */

string BankAccount::_dbTable = "bank_account";

BankAccount::BankAccount(unsigned int user_id, const string swift, const string bic) :_idUser(user_id),
                                                                                         _swift(swift),
                                                                                         _bic(bic) {
    _id = 0;
}

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

void BankAccount::setBalance(int balance) {
    _balance = balance;
}

int BankAccount::getBalance() {
    return _balance;
}

BankAccount::BankAccount(){
    _id = 0;
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
    _idUser = idUser;
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
    cout << "Expenses for account: " << getId() << endl;
    set<int> expenses = getExpenses();
    for (auto j : expenses) {
        Transaction* transaction = new Transaction(j);
        cout << *transaction << endl;
    }
}

void BankAccount::decreaseAmount(int less) {
    _balance -= less;
}

set<int> BankAccount::getExpenses() {
    map<int, map<string, string>> expenses = BaseModel::select("transactions", "id", "account = " + to_string(getId()));

    int totalExpenses = (int)expenses.size();

    set<int> ExpensesId = set<int>();

    for (int i = 1; i != totalExpenses + 1; i++)
    {
        ExpensesId.insert(stoi(expenses[i]["id"]));
    }

    return ExpensesId;
}

void BankAccount::RequestSwift() {
    cout << "Swift:" << getSwift() << endl;
    cout << "Bic:" << getBic() << endl;
}


ostream& operator<< (ostream& stream, const BankAccount& bankAccount)
{
    User* user = new Client(bankAccount._idUser);
    stream << "Bank account number: "<< bankAccount.getId()<<endl;
    stream << "Owner: " << user->getFirstName() << " " << user->getLastName() << endl;
    stream << "Balance: " << bankAccount._balance << endl;

    return stream;
}

istream& operator>> (std::istream& stream, BankAccount& bankAccount)
{
    cout << "Creation BankAccount: " << endl;
    cout << "Swift: " << endl;
    stream >> bankAccount._swift;
    cout << "BIC: " << endl;
    stream >> bankAccount._bic;
    cout << "Balance: " << endl;
    stream >> bankAccount._balance;

    return stream;

}

void BankAccount::getusersIDS() {

    BankAccount* test = new BankAccount();

    map<int, map<string, string>> users = BaseModel::select("users", "id, name, surname, isadmin, isadvisor");
    int totalUsers = (int)users.size();
    set<int> userIds = set<int>();

    for (int i = 1; i != totalUsers + 1; i++)
    {
        string space, star = "";

        int spaceNumber;

        if (stoi(users[i]["id"]) < 10) {
            spaceNumber = 11;

        }
        else {
            spaceNumber = 10;
        }

        for(unsigned int i = 0; i < (spaceNumber - users[i]["id"].length()); i++){
            space += " ";
        }

        if (users[i]["isadmin"] == "1")
        {
            star = "**";
        }
        if(users[i]["isadvisor"] == "1"){
            star = "*";
        }

        cout << space << users[i]["id"] << " | " << star << users[i]["name"] << " " << users[i]["surname"] << endl;
        userIds.insert(stoi(users[i]["id"]));
    }

}

bool BankAccount::remove()
{
    return BaseModel::remove(_dbTable, _id);
}
