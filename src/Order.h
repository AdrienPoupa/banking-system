/**
 * Project Untitled
 */


#ifndef _ORDER_H
#define _ORDER_H

#include "Date.h"

class Order {
protected:
    unsigned int _id;
    Date _creation;
    Date _sent;
    char _type;
    unsigned int _user_id;
public:
    Order(const Date creation, const Date sent, char type, unsigned int user_id);

    // todo: Order from ID

    unsigned int getId();

    void setCreation(Date creation);
    Date getCreation();

    void setSent(Date sent);
    Date getSent();

    void setType(char type);
    char getType();

    void setUserId(unsigned int user_id);
    unsigned int getUserId();

    void OrderCheckbook();

    void OrderCreditCard();

    bool save();
};

#endif //_ORDER_H
