#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include <set>
#include <iostream>

#include "Address.h"
#include "../sqlite/SQLiteCpp.h"
#include "Date.h"

class User {
protected:
    Address _address;
    std::string _phone;
    int _isAdmin = 0;
    std::string _password;

    static std::string _dbTable;

    unsigned int _id;
    std::string _lastName;
    std::string _firstName;
    Date _birthDate;

public:
   /* User(const std::string firstName, const std::string lastName, const Date birthDate,
         const std::string phone = "Inconnu", const int _isAdmin = 0, const int _quota = 1, const std::string password = "");
    User();
    ~User();*/
    User(int id); // Get a person from an ID provided by DB

    User(const std::string lastName = "John", const std::string firstName = "Doe", const std::string password = "123");
    User(const std::string lastName, const std::string firstName, const Date birthDate);
    

    unsigned int getId() const;

    std::string getLastName() const;
    void setLastName(const std::string lastName);

    std::string getFirstName() const;
    void setFirstName(const std::string firstName);

    Date getBirthDate() const;
    void setBirthDate(const Date birthDate);


    void editFirstname();
    void editLastname();
    void editBirthdate();

    void init(std::map<std::string, std::string> data);
    void deserialization(std::map<std::string, std::string> data);

    std::string getPhone() const ;
    void setPhone(const std::string phone);

    void setPassword(const std::string password);
    bool checkPassword(const std::string password) const;

    Address getAddress()const ;
    void setAddress(const Address address);

    bool isAdmin()const ;
    void setAdmin(const int isAdmin);

    void getBankAccounts();
    void edit();

    bool save();
    bool remove();

    void shortDisplay() const;

    friend std::ostream& operator<< (std::ostream& stream, const User& user);
    friend std::istream& operator>> (std::istream& stream, User& user);
};

#endif /* User_hpp */
