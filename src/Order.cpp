/**
 * Project Untitled
 */


#include "Order.h"
#include "BaseModel.h"
#include "Client.h"

using namespace std;

/**
 * Order implementation
 */

string Order::_dbTable = "orders";

Order::Order(const Date creation, const Date sent, int type, User user) : _creation(creation),
                                                                               _sent(sent),
                                                                                _type(type),
                                                                               _user(user) { }

Order::Order(const unsigned int id) {
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if (!data.empty())
    {
        _id = id;
        _creation = Date(data["creation"]);
        _sent = Date(data["sent"]);
        _type = stoi(data["type"]);
        _user = Client((unsigned) stoi(data["user"]));
    }
    else
    {
        throw invalid_argument("Please enter a valid ID");
    }
}

unsigned int Order::getId() {
    return _id;
}

void Order::setCreation(Date creation) {
    _creation = creation;
}

Date Order::getCreation() {
    return _creation;
}

void Order::setSent(Date sent) {
    _sent = sent;
}

Date Order::getSent() {
    return _sent;
}

void Order::setType(int type) {
    _type = type;
}

int Order::getType() {
    return _type;
}

void Order::setUser(User user) {
    _user = user;
}

User Order::getUser() {
    return _user;
}

void Order::OrderCheckbook() {

}

void Order::OrderCreditCard() {

}

bool Order::save()
{
    int res = BaseModel::save(_dbTable, {
            {"id", {to_string(_id), "int"}},
            {"creation", {_creation.dateToDB(), "string"}},
            {"sent", {_sent.dateToDB(), "string"}},
            {"user", {to_string(_user.getId()), "int"}},
            {"type", {to_string(_type), "int"}},
    });
    if (_id == 0)
    {
        _id = res["id"];
    }

    return (bool) res;
}
bool Order::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

// todo everywhere: load >> <<