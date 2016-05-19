/**
 * Project Untitled
 */


#ifndef _ORDER_H
#define _ORDER_H

#include "Date.h"
#include "User.h"
#include "Client.h"

class Order {
protected:
    unsigned int _id;
    Date _creation;
    Date _sent;
    int _type;
    Client _user;
    BankAccount _account;

    static std::string _dbTable;
public:
    Order(const Date creation, const Date sent, int type, Client user, BankAccount account);
    Order(const unsigned int id);
    Order();

    unsigned int getId();

    void setCreation(Date creation);
    Date getCreation();

    void setSent(Date sent);
    Date getSent();

    void setAccount(BankAccount account);
    BankAccount getAccount();

    void setType(int type);
    int getType();

    void setClient(Client user);
    Client getClient();

    void OrderCheckbook();

    void OrderCreditCard();

    bool save();

    bool remove();

    friend std::ostream& operator<< (std::ostream& stream, const Order& order);
    friend std::istream& operator>> (std::istream& stream, Order& order);
};

#endif //_ORDER_H
