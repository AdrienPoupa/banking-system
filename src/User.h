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
    int _isAdvisor = 0;
    int _idAdvisor;
    std::string _password;

    static std::string _dbTable;

    unsigned int _id;
    std::string _lastName;
    std::string _firstName;
    Date _birthDate;

public:
    unsigned int getId() const;

    std::string getLastName() const;
    void setLastName(const std::string lastName);

    std::string getFirstName() const;
    void setFirstName(const std::string firstName);

    std::string getPassword() const;
    Date getBirthDate() const;
    void setBirthDate(const Date birthDate);


    void editFirstname();
    void editLastname();
    void editBirthdate();

    std::string getPhone()  const;
    void setPhone(const std::string phone);

    void setPassword(const std::string password);
    bool checkPassword(const std::string password) const;

    Address getAddress() const;
    void setAddress(const Address address);

    bool isAdmin() const;
    void setAdmin(const int isAdmin);

    void edit();

    bool save();
    bool remove();

    void shortDisplay() const;

    bool isAdvisor() const;
    
    friend std::ostream& operator<< (std::ostream& stream, const User& user);
    friend std::istream& operator>> (std::istream& stream, User& user);

    virtual ~User() = 0;
};

#endif /* User_hpp */
