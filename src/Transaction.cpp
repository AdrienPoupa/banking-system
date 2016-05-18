//
// Created by Adrien on 17/05/2016.
//

#include "Transaction.h"

using namespace std;

string Transaction::_dbTable = "transactions";

Transaction::Transaction(const BankAccount account, const Date date, int amount, const string description)
        : _account(account), _date(date), _amount(amount), _description(description) { }

Transaction::Transaction(const unsigned int id) {
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if (!data.empty())
    {
        _id = id;
        _account = BankAccount(stoi(data["account"]));
        _date = Date(data["date"]);
        _amount = stoi(data["amount"]);
        _description = data["description"];
    }
    else
    {
        throw invalid_argument("Please enter a valid ID");
    }
}

unsigned int Transaction::getId() const {
    return _id;
}

void Transaction::setBankAccount(BankAccount account) {
    _account = account;
}

BankAccount Transaction::getBankAccount() {
    return _account;
}

void Transaction::setDate(Date date) {
    _date = date;
}

Date Transaction::getDate() {
    return _date;
}

void Transaction::setAmount(int amount) {
    _amount = amount;
}

int Transaction::getAmount() {
    return _amount;
}

void Transaction::setDescription(std::string description) {
    _description = description;
}

std::string Transaction::getDescription() {
    return _description;
}

bool Transaction::save()
{
    int res = BaseModel::save(_dbTable, {
            {"id", {to_string(_id), "int"}},
            {"account", {to_string(_account.getId()), "int"}},
            {"date", {_date.dateToDB(), "string"}},
            {"amount", {to_string(_amount), "int"}},
            {"description", {_description, "string"}}
    });
    if (_id == 0)
    {
        _id = res["id"];
    }

    return (bool) res;
}
bool Transaction::remove()
{
    return BaseModel::remove(_dbTable, _id);
}