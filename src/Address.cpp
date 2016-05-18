#include "Address.h"
#include <iostream>

using namespace std;

Address::Address(const int& houseNumber, const std::string& streetName, const std::string& postalCode, const std::string& town, const std::string& country):
    _houseNumber(houseNumber), _streetName(streetName), _postalCode(postalCode), _town(town), _country(country)
{
    // empty
}

string Address::getCountry() const
{
    return _country;
}

void Address::setCountry(const string& pays)
{
    _country = pays;
}

int Address::getHouseNumber() const
{
    return _houseNumber;
}

void Address::setHouseNumber(const int &numero)
{
    _houseNumber = numero;
}

string Address::getPostalCode() const
{
    return _postalCode;
}

void Address::setPostalCode(const string &postalCode)
{
    _postalCode = postalCode;
}

string Address::getTown() const
{
    return _town ;
}

void Address::setTown(const string& ville)
{
    _town = ville ;
}

string Address::getStreetName() const
{
    return _streetName;
}

void Address::setStreetName(const string& streetName)
{
    _streetName = streetName;
}

ostream& operator<< (ostream& stream, const Address& address)
{
    stream << address._houseNumber << " " << address._streetName << ", " << address._postalCode << " " << address._town << ", " << address._country;
    return stream;
}

istream& operator>> (std::istream& stream, Address& address)
{
    cout << "Street number: " << endl;
    stream >> address._houseNumber;
    cout << "Street: " << endl;
    stream.ignore(1, '\n');
    getline(stream, address._streetName, '\n');
    cout << "Postal code: " << endl;
    getline(stream, address._postalCode, '\n');
    cout << "Town: " << endl;
    getline(stream, address._town, '\n');
    cout << "Country: " << endl;
    getline(stream, address._country, '\n');

    return stream;

}
