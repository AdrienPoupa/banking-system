/**
 * Project Untitled
 */


#include "Loan.h"
#include "BaseModel.h"
#include "Client.h"

using namespace std;

string Loan::_dbTable = "loans";

/**
 * Loan implementation
 */

Loan::Loan(const Date creation, const Date validation, const User sender, const bool approved) : _creation(creation),
                                                                                                 _validation(validation),
                                                                                                _sender(sender),
                                                                                                _approved(approved){
    _id = 0;
}

Loan::Loan(const unsigned int id) {
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if (!data.empty())
    {
        _id = id;
        _sender = Client((unsigned) stoi(data["sender"]));
        _creation = Date(data["creation"]);
        _validation = Date(data["validation"]);
        _approved = (bool) stoi(data["approved"]);
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

bool Loan::getApproved() {
    return _approved;
}

void Loan::validate() {
    _approved = true;
}

void Loan::decline() {
    _approved = false;
}

bool Loan::save()
{
    int res = BaseModel::save(_dbTable, {
            {"id", {to_string(_id), "int"}},
            {"creation", {_creation.dateToDB(), "string"}},
            {"validation", {_validation.dateToDB(), "string"}},
            {"sender", {to_string(_sender.getId()), "int"}},
            {"approved", {to_string(_approved), "int"}}
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
    stream << "Validation date:" << loan._validation << endl;
    stream << "Sender:" << endl;
    stream << loan._sender << endl;
    stream << "Approved:" << loan._approved << endl;
    return stream;
}

istream& operator>> (std::istream& stream, Loan& loan)
{
    cout << "Creation date: " << endl;
    stream >> loan._creation;
    cout << "Validation date: " << endl;
    stream >> loan._validation;
    cout << "Sender: " << endl;
    int userID;
    stream >> userID;
    loan._sender = *new Client(userID);
    cout << "Approved (0 or 1): " << endl;
    stream >> loan._approved;

    return stream;

}
