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

Order::Order(const Date creation, const Date sent, int type, Client user) : _creation(creation),
                                                                               _sent(sent),
                                                                                _type(type),
                                                                               _user(user) {
    _id = 0;
}

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

void Order::setUser(Client user) {
    _user = user;
}

Client Order::getUser() {
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

ostream& operator<< (ostream& stream, const Order& order)
{
    stream << "Creation date:" << order._creation << endl;
    stream << "Sent:" << order._sent << endl;
    stream << "Type:" << order._type << endl;
    stream << "User:" << endl;
    stream << order._user << endl;
    return stream;
}

istream& operator>> (std::istream& stream, Order& order)
{
    cout << "Creation date: " << endl;
    stream >> order._creation;
    cout << "Sent: " << endl;
    stream >> order._sent;
    cout << "Type: " << endl;
    stream >> order._type;
    cout << "User ID: " << endl;
    int userID;
    stream >> userID;
    order._user = *new Client(userID);

    return stream;

}
