#include <thread>
#include <iostream>
#include "User.h"
#include "BaseModel.h"
#include "sha256.h"

using namespace std;

/* Database Model
 Table: users

 Columns:
 - id: INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
 - name: TEXT NOT NULL,
 - surname: TEXT NOT NULL,
 - phone: TEXT,
 - birthdate: DATE,
 - country: TEXT,
 - house_number: INTEGER,
 - postal_code: TEXT,
 - town: TEXT,
 - street: TEXT

 */

string User::_dbTable = "users";

/*User::User(const std::string firstName, const std::string lastName, const Date birthDate, const string phone,
           const int isAdmin, const int quota, const string password):
    User(firstName, lastName, birthDate), _phone(phone), _isAdmin(isAdmin), _quota(quota), _password(password)
{

}

User::User()
{
    _firstName = "John";
    _lastName = "Doe";

    _birthDate = Date();

    _phone = "Inconnu";
}
*/
/*
User::~User()
{

}*/

unsigned int User::getId() const {
    return _id;
}

void User::init(map<string, string> data){
    this->deserialization(data);
}

void User::deserialization(map<string, string> data){
    if(!data.empty()){
        _id = data.find("id") != data.end() ? stoi(data["id"]) : 0;
        _firstName = data["name"];
        _lastName = data["surname"];
        _birthDate = data.find("birthdate") != data.end() ? Date(data["birthdate"]) : Date();
        _phone = data["phone"];
        _address = Address(data.find("house_number") != data.end() ? stoi(data["house_number"]) : 0, data["street"], data["postal_code"], data["town"], data["country"]);
        _isAdmin = data.find("isadmin") != data.end() ? stoi(data["isadmin"]) : 0;
        _isAdvisor=data.find("isadvisor") != data.end() ? stoi(data["isadvisor"]) : 0;
        _password = data["password"];
    }
}

string User::getPhone() const
{
    return _phone;
}
string User::getPassword() const
{
    return _password;
}
void User::setPhone(const string phone)
{
    _phone = phone;
}

void User::setPassword(const string password)
{
    _password = sha256(password);
}

bool User::checkPassword(const string password) const
{
    if (sha256(password) == _password)
    {
        return true;
    }

    return false;
}

Address User::getAddress() const
{
    return _address;
}

void User::setAddress(const Address address)
{
    _address = address;
}

bool User::isAdmin() const
{
    return (bool) _isAdmin;
}

bool User::isAdvisor() const
{
    return (bool) _isAdvisor;
}

void User::setAdmin(const int isAdmin)
{
    if (isAdmin == 0 || isAdmin == 1)
    {
        _isAdmin = isAdmin;
    }
}

string User::getLastName() const
{
    return _lastName;
}

void User::setLastName(const string lastName)
{
    _lastName = lastName;
}

void User::setFirstName(const string firstName)
{
    _firstName = firstName;
}

string User::getFirstName() const
{
    return _firstName;
}

Date User::getBirthDate() const
{
    return _birthDate;
}

void User::setBirthDate(const Date birthDate)
{
    _birthDate = birthDate;
}

void User::editFirstname(){
    cout << "Enter new firstname: " << endl;
    string newName;
    cin.ignore(1, '\n');
    getline(cin, newName, '\n');
    setFirstName(newName);
}
void User::editLastname(){
    cout << "Enter new last name: " << endl;
    string newLastName;
    cin.ignore(1, '\n');
    getline(cin, newLastName, '\n');
    setLastName(newLastName);
}
void User::editBirthdate(){
    cout << "Enter new birthdate: " << endl;
    Date newBirthDate;
    cin >> newBirthDate;
    setBirthDate(newBirthDate);
}

void User::edit()
{
    int choice;
    bool failInput = false;
    do {
        cout << "-------------------------------------" << endl;
        cout << " -- Edit a user -- " << endl;

        cout << "1. Edit first name" << endl;
        cout << "2. Edit last name" << endl;
        cout << "3. Edit phone number" << endl;
        cout << "4. Edit birthdate" << endl;
        cout << "5. Edit address" << endl;
        cout << "6. Edit permissions" << endl;
        cout << "8. Edit password" << endl;
        cout << "9. Delete user" << endl;
        cout << "0. Cancel" << endl;

        cout << "Choice: " << endl;
        cin >> choice;
        if(cin.fail()){
            failInput = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while(failInput || choice < 0 || choice > 9);

    switch (choice)
    {
        case 1:
        {
            editFirstname();
            break;
        }
        case 2:
        {
            editLastname();
            break;
        }
        case 3:
        {
            cout << "Enter new phone : " << endl;
            string newPhone;
            cin.ignore(1, '\n');
            getline(cin, newPhone, '\n');
            setPhone(newPhone);
            break;
        }
        case 4:
        {
            editBirthdate();
            break;
        }
        case 5:
        {
            cout << "Enter new address : " << endl;
            Address newAddress;
            cin >> newAddress;
            setAddress(newAddress);
            break;
        }
        case 6:
        {
            int newIsAdmin;
            bool failInput;
            do {
                failInput = false;
                // todo: update
                cout << "Type 0 for a regular user, 1 for an admin : " << endl;
                cin >> newIsAdmin;
                if(cin.fail()){
                    failInput = true;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }while(failInput);
            setAdmin(newIsAdmin);
            break;
        }
        case 8:
        {
            cout << "Enter new password: " << endl;
            string newPassword;
            cin.ignore(1, '\n');
            getline(cin, newPassword, '\n');
            setPassword(newPassword);
            break;
        }
        case 9:
        {
            remove();
            throw invalid_argument("You just deleted yourself");
            break;
        }
        default:
            return;
            break;
    }

    if (choice != 9 && choice != 0 )
    {
        cout << "Saving..." << endl;
        save();
    }

    return;
}

bool User::save()
{
    int res = BaseModel::save(_dbTable, {
        {"id", {to_string(_id), "int"}},
        {"name", {_firstName, "string"}},
        {"surname", {_lastName, "string"}},
        {"phone", {_phone, "string"}},
        {"birthdate", {_birthDate.dateToDB(), "string"}},
        {"country", {_address.getCountry(), "string"}},
        {"house_number", {to_string(_address.getHouseNumber()), "int"}},
        {"postal_code", {_address.getPostalCode(), "string"}},
        {"town", {_address.getTown(), "string"}},
        {"street", {_address.getStreetName(), "string"}},
        {"isadmin", {to_string(_isAdmin), "int"}},
        {"password", {_password, "string"}}
    });
    if (_id == 0)
    {
        _id = res["id"];
    }

    return (bool) res;
}
bool User::remove()
{
    return BaseModel::remove(_dbTable, _id);
}

void User::shortDisplay() const
{
    cout << _id << ". " << _firstName << " " << _lastName << endl;
}

ostream& operator<< (ostream& stream, const User& user)
{
    string isAdmin = "No";

    if (user._isAdmin == true)
    {
        isAdmin = "Yes";
    }

    stream << user._id << ". " << user._firstName << " " << user._lastName << endl;
    stream << "Birthdate: " << user._birthDate << endl;
    stream << "Phone: " << user._phone << endl;
    stream << "Adress: " << user._address << endl;
    stream << "Is admin: " << isAdmin << endl;

    return stream;
}

istream& operator>> (istream& stream, User& user)
{
    string passwordTmp;

    cout << "New user" << endl;

    cout << "First name: " << endl;
    stream.ignore(1, '\n');
    getline(stream, user._firstName, '\n');

    cout << "Last name: " << endl;
    getline(stream, user._lastName, '\n');

    cout << "Birthdate: " << endl;
    stream >> user._birthDate;

    cout << "Phone: " << endl;
    stream.ignore(1, '\n');
    getline(stream, user._phone, '\n');

    cout << "Address: " << endl;
    stream >> user._address;

    cout << "Password: " << endl;
    stream.ignore(1, '\n');
    getline(stream, passwordTmp, '\n');

    cout << "Type 0 for a regular user, 1 for an admin:" << endl;
    bool a;
    bool failInput;
    do {
        failInput = false;
        stream >> a;
        if(stream.fail()){
            failInput = true;
            stream.clear();
            stream.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }while(failInput);
    user._isAdmin = a;

    // Insert the hashed password
    user._password = sha256(passwordTmp);

    return stream;
}
