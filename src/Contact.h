//
// Created by Adrien Le Roy on 18/05/2016.
//

#ifndef BANKING_SYSTEM_CONTACT_H
#define BANKING_SYSTEM_CONTACT_H
#include <stdio.h>
#include <set>
#include <iostream>
#include "BankAccount.h"
#include "Contact.h"
#include "User.h"
#include "BaseModel.h"
#include "Client.h"

class Contact{
protected:
    unsigned int _id;
    unsigned int _idClient;
    unsigned int _idAdvisor;
    std::string _dateMessage;
    int _read;
    std::string _message;
    static std::string _dbTable;
public:
    Contact(unsigned int idUser, unsigned int idAvisor, std::string message);
    Contact(int unsigned id); // Get a message from an ID provided by DB
    bool save();
    bool isRead();
    void read();
    friend std::ostream& operator<< (std::ostream& stream, const Contact& contact);

};
#endif //BANKING_SYSTEM_CONTACT_H
