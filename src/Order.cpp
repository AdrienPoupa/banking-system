/**
 * Banking system
 */


#include "Order.h"
#include "BaseModel.h"
#include "Client.h"
#include "Notification.h"

using namespace std;

/**
 * Order implementation
 */

string Order::_dbTable = "orders";

Order::Order(const Date creation, const Date sent, int type, Client user, BankAccount account) : _creation(creation),
                                                                               _sent(sent),
                                                                                _type(type),
                                                                               _user(user),
                                                                                _account(account){
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
        _user = Client((unsigned) stoi(data["user_id"]));
        _account = BankAccount((unsigned) stoi(data["account"]));
    }
    else
    {
        throw invalid_argument("Please enter a valid ID");
    }
}

Order::Order() {
    _id = 0;
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

void Order::setAccount(BankAccount account) {
    _account = account;
}

BankAccount Order::getAccount() {
    return _account;
}

void Order::setType(int type) {
    _type = type;
}

int Order::getType() {
    return _type;
}

void Order::setClient(Client user) {
    _user = user;
}

Client Order::getClient() {
    return _user;
}

void Order::OrderCheckbook() {

    map<int, map<string, string>> orders = BaseModel::select("orders", "id",
                                                            "user_id = " + to_string(_user.getId()) + " AND sent = '0001-01-01'");

    int totalOrders = (int)orders.size();

    if (totalOrders > 0) {
        cout << "You already have an order pending" << endl;
    }
    else {
        Date* today = new Date();
        Date* sent = new Date(-1, -1, -1);
        this->setCreation(*today);
        this->setSent(*sent);
        this->setType(0);
        this->save();

        // Notify the advisor
        string notificationMessage = "New checkbook order from "
                                     + _user.getLastName() + " " + _user.getFirstName();
        Notification* notification = new Notification(notificationMessage, (unsigned) _user.getAdvisor());
        notification->save();
    }
}

void Order::OrderCreditCard() {
    map<int, map<string, string>> orders = BaseModel::select("orders", "id",
                                                             "user_id = " + to_string(_user.getId()) + " AND sent = '0001-01-01'");

    int totalOrders = (int)orders.size();

    if (totalOrders > 0) {
        cout << "You already have an order pending" << endl;
    }
    else {
        Date *today = new Date();
        Date *sent = new Date(-1, -1, -1);
        this->setCreation(*today);
        this->setSent(*sent);
        this->setType(1);
        this->save();

        // Notify the advisor
        string notificationMessage = "New credit card order from "
                                     + _user.getLastName() + " " + _user.getFirstName();
        Notification* notification = new Notification(notificationMessage, (unsigned) _user.getAdvisor());
        notification->save();
    }
}

bool Order::save()
{
    int res = BaseModel::save(_dbTable, {
            {"id", {to_string(_id), "int"}},
            {"creation", {_creation.dateToDB(), "string"}},
            {"sent", {_sent.dateToDB(), "string"}},
            {"user_id", {to_string(_user.getId()), "int"}},
            {"type", {to_string(_type), "int"}},
            {"account", {to_string(_account.getId()), "int"}},
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
    if (order._type == '0') {
        stream << "Type: Checkbook" << endl;
    }
    else {
        stream << "Type: Credir card" << endl;
    }
    stream << "User:" << endl;
    stream << order._user << endl;
    stream << order._account << endl;
    return stream;
}

istream& operator>> (std::istream& stream, Order& order)
{
    cout << "Creation date: " << endl;
    stream >> order._creation;
    cout << "Sent: " << endl;
    stream >> order._sent;
    cout << "Type (0 for checkbook, 1 for credit card): " << endl;
    stream >> order._type;
    cout << "User ID: " << endl;
    int userID;
    stream >> userID;
    order._user = *new Client((unsigned) userID);
    cout << "BankAccount ID: " << endl;
    int bankID;
    stream >> bankID;
    order._account = *new BankAccount((unsigned) bankID);

    return stream;

}
