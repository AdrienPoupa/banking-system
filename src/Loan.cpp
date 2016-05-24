/**
 * Banking system
 */


#include "Loan.h"
#include "BaseModel.h"
#include "Client.h"
#include "Notification.h"

using namespace std;

string Loan::_dbTable = "loans";

/**
 * Loan implementation
 */

Loan::Loan(const Date creation, const Date validation, const User sender, const bool approved, const int amount, const int advisorId) :_creation(creation),
                                                                                                 _validation(validation),
                                                                                                _sender(sender),
                                                                                                _approved(approved),
                                                                                                _advisorId(advisorId),
                                                                                                _amount(amount){
    _id = 0;
}

Loan::Loan() {
    _creation = *new Date();
    _validation = *new Date(-1, -1, -1);
    _id = 0;
    _approved = false;
}

Loan::Loan(const unsigned int id) {
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if (!data.empty())
    {
        _id = id;
        _sender = Client((unsigned) stoi(data["sender"]));
        _advisorId = stoi(data["advisor_id"]);
        _creation = Date(data["creation"]);
        _validation = Date(data["validation"]);
        _approved = (bool) stoi(data["approved"]);
        _amount = stoi(data["amount"]);
    }
    else
    {
        throw invalid_argument("Please enter a valid ID");
    }
}

unsigned int Loan::getId() const {
    return _id;
}

void Loan::setCreation(Date creation) {
    _creation = creation;
}

Date Loan::getCreation() {
    return _creation;
}

void Loan::setValidation(Date validation) {
    _validation = validation;
}

Date Loan::getValidation() {
    return _validation;
}

void Loan::setSender(User sender) {
    _sender = sender;
}

User Loan::getSender() {
    return _sender;
}

void Loan::setAdvisor(int advisorId) {
    _advisorId = advisorId;
}

int Loan::getAdvisor() {
    return _advisorId;
}

bool Loan::getApproved() {
    return _approved;
}

void Loan::setAmount(int amount) {
    _amount = amount;
}

int Loan::getAmount() {
    return _amount;
}

void Loan::validate() {
    _approved = true;
    _validation = *new Date();
    this->save();

    // Create a new account with the amount
    BankAccount* loanAccount = new BankAccount(_sender.getId(), BankAccount::random_string(11), BankAccount::random_string(8), _amount);
    loanAccount->save();

    // Notify the user
    string notificationMessage = "Your loan inquiry for " + to_string(_amount) + " has been approved";
    Notification* notification = new Notification(notificationMessage, _sender.getId());
    notification->save();
}

void Loan::decline() {
    _approved = false;
    _validation = *new Date();
    this->save();

    // Notify the user
    string notificationMessage = "Your loan inquiry for " + to_string(_amount) + " has been refused";
    Notification* notification = new Notification(notificationMessage, _sender.getId());
    notification->save();
}

bool Loan::save()
{
    int res = BaseModel::save(_dbTable, {
            {"id", {to_string(_id), "int"}},
            {"creation", {_creation.dateToDB(), "string"}},
            {"validation", {_validation.dateToDB(), "string"}},
            {"sender", {to_string(_sender.getId()), "int"}},
            {"advisor_id", {to_string(_advisorId), "int"}},
            {"amount", {to_string(_amount), "int"}},
            {"approved", {to_string((int) _approved), "int"}}
    });
    if (_id == 0)
    {
        _id = res["id"];
    }

    return (bool) res;
}

bool Loan::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

ostream& operator<< (ostream& stream, const Loan& loan)
{
    stream << "Creation date:" << loan._creation << endl;
    stream << "Validation (or refusal) date:" << loan._validation << endl;
    stream << "Sender:" << endl;
    stream << loan._sender << endl;
    stream << "Approved:" << loan._approved << endl;
    stream << "Amount:" << loan._amount << endl;
    return stream;
}

istream& operator>> (std::istream& stream, Loan& loan)
{
    cout << "Amount required: " << endl;
    stream >> loan._amount;

    return stream;
}
