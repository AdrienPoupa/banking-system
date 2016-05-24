//
// Notification class
//

#include "Notification.h"
#include "BaseModel.h"

using namespace std;

string Notification::_dbTable = "notifications";

Notification::Notification() {
    _id = 0;
    _read = false;
}

Notification::Notification(unsigned int id) {
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if (!data.empty())
    {
        _id = id;
        _message = data["message"];
        _userId = (unsigned) stoi(data["userid"]);
        _read = (bool) stoi(data["read"]);
    }
    else
    {
        throw invalid_argument("Please enter a valid ID");
    }
}

Notification::Notification(string message, unsigned int userId) : _message(message), _userId(userId) {
    _id = 0;
}

unsigned int Notification::getId() {
    return _id;
}

void Notification::setId(unsigned int id) {
    _id = id;
}

std::string Notification::getMessage() {
    return _message;
}

void Notification::setMessage(std::string message) {
    _message = message;
}

unsigned int Notification::getUserId() {
    return _userId;
}

void Notification::setUserId(unsigned int userId) {
    _userId = userId;
}

bool Notification::getRead() {
    return _read;
}

void Notification::setRead(bool read) {
    _read = read;
}

bool Notification::save() {
    int res = BaseModel::save(_dbTable, {
            {"id", {to_string(_id), "int"}},
            {"message", {_message, "string"}},
            {"userid", {to_string(_userId), "int"}},
            {"read", {to_string((int) _read), "int"}},
    });

    if (_id == 0)
    {
        _id = res["id"];
    }

    return (bool) res;
}

bool Notification::remove() {
    return BaseModel::remove(_dbTable, _id);
}

std::ostream& operator<< (std::ostream& stream, const Notification& notification) {
    stream << notification._message << endl;

    return stream;
}

std::istream& operator>> (std::istream& stream, Notification& notification) {
    cout << "Message:" << endl;
    stream.ignore(1, '\n');
    getline(stream, notification._message, '\n');

    return stream;
}