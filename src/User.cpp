#include <thread>
#include <c++/iostream>
#include "User.h"
#include "Address.h"
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

User::User(const int id) // Get a User from an ID provided by DB
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if (!data.empty())
    {
        _id = id;
        _firstName = data["name"];
        _lastName = data["surname"];
        _birthDate = Date(data["birthdate"]);
        _phone = data["phone"];
        _address = Address(stoi(data["house_number"]), data["street"], data["postal_code"], data["town"], data["country"]);
        _isAdmin = stoi(data["isadmin"]);
        _quota = stoi(data["quota"]);
        _password = data["password"];
    }
    else
    {
        throw invalid_argument("Merci d'entrer un utilisateur valide");
    }
}

User::~User()
{

}*/

User::User(const std::string lastName, const std::string firstName) {
    _lastName = lastName;
    _firstName = firstName;
}

User::User(const std::string lastName, const std::string firstName, const Date birthDate) {
    _lastName = lastName;
    _firstName = firstName;
    _birthDate = birthDate;
}

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
        _password = data["password"];
    }
}

string User::getPhone() const
{
    return _phone;
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
    cout << "Saisir nouveau prenom : " << endl;
    string newName;
    cin.ignore(1, '\n');
    getline(cin, newName, '\n');
    setFirstName(newName);
}
void User::editLastname(){
    cout << "Saisir nouveau nom : " << endl;
    string newLastName;
    cin.ignore(1, '\n');
    getline(cin, newLastName, '\n');
    setLastName(newLastName);
}
void User::editBirthdate(){
    cout << "Saisir nouvelle date de naissance : " << endl;
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
        cout << " -- Modification d'un utilisateur -- " << endl;

        cout << "1. Modifier le prenom" << endl;
        cout << "2. Modifier le nom" << endl;
        cout << "3. Modifier le telephone" << endl;
        cout << "4. Modifier la date de naissance" << endl;
        cout << "5. Modifier l'adresse" << endl;
        cout << "6. Modifier le type de compte" << endl;
        cout << "8. Modifier le mot de passe" << endl;
        cout << "9. Supprimer l'utilisateur" << endl;
        cout << "0. Annuler" << endl;

        cout << "Choix: " << endl;
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
            cout << "Saisir nouveau numero de telephone : " << endl;
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
            cout << "Saisir nouvelle adresse : " << endl;
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
                cout << "Tapez 0 pour un utilisateur lambda, 1 pour un administrateur : " << endl;
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
            cout << "Saisir nouveau mot de passe : " << endl;
            string newPassword;
            cin.ignore(1, '\n');
            getline(cin, newPassword, '\n');
            setPassword(newPassword);
            break;
        }
        case 9:
        {
            remove();
            throw invalid_argument("Vous venez de vous supprimer");
            break;
        }
        default:
            return;
            break;
    }

    if (choice != 9 && choice != 0 )
    {
        cout << "Sauvegarde..." << endl;
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
    string isAdmin = "Non";

    if (user._isAdmin == true)
    {
        isAdmin = "Oui";
    }

    stream << user._id << ". " << user._firstName << " " << user._lastName << endl;
    stream << "Anniversaire: " << user._birthDate << endl;
    stream << "Telephone: " << user._phone << endl;
    stream << "Adresse: " << user._address << endl;
    stream << "Est admin: " << isAdmin << endl;

    return stream;
}

istream& operator>> (istream& stream, User& user)
{
    string passwordTmp;

    cout << "Saisie d'un utilisateur" << endl;

    cout << "Saisie du prenom : " << endl;
    stream.ignore(1, '\n');
    getline(stream, user._firstName, '\n');

    cout << "Saisie du nom : " << endl;
    getline(stream, user._lastName, '\n');

    cout << "Saisie de l'anniversaire : " << endl;
    stream >> user._birthDate;

    cout << "Saisie du telephone : " << endl;
    stream.ignore(1, '\n');
    getline(stream, user._phone, '\n');

    cout << "Saisie de l'adresse : " << endl;
    stream >> user._address;

    cout << "Saisie du mot de passe : " << endl;
    stream.ignore(1, '\n');
    getline(stream, passwordTmp, '\n');

    cout << "Tapez 1 si l'utilisateur est administrateur, 0 sinon : " << endl;
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
