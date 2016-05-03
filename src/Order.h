/**
 * Project Untitled
 */


#ifndef _ORDER_H
#define _ORDER_H

#include "Date.h"

class Order {
public:
    Date creation;
    Date sent;
    char type;

    void OrderCheckbook();

    void OrderCreditCard();
};

#endif //_ORDER_H
