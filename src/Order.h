/**
 * Project Untitled
 */


#ifndef _ORDER_H
#define _ORDER_H

#include "Date.h"
#include "User.h"

class Order {
protected:
    unsigned int _id;
    Date _creation;
    Date _sent;
    int _type;
    User _user;

    static std::string _dbTable;
public:
    Order(const Date creation, const Date sent, int type, User user);
    Order(const unsigned int id);

    unsigned int getId();

    void setCreation(Date creation);
    Date getCreation();

    void setSent(Date sent);
    Date getSent();

    void setType(int type);
    int getType();

    void setUser(User user);
    User getUser();

    void OrderCheckbook();

    void OrderCreditCard();

    bool save();

    bool remove();
};

#endif //_ORDER_H
