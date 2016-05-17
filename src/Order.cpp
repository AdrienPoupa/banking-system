/**
 * Project Untitled
 */


#include "Order.h"

/**
 * Order implementation
 */

Order::Order(const Date creation, const Date sent, char type, unsigned int user_id) : _creation(_creation),
                                                                               _sent(_sent), _type(_type),
                                                                               _user_id(_user_id) { }

unsigned int Order::getId() {
    return _id;
}

void Order::setCreation(Date creation) {
    _creation = creation;
}

Date Order::getCreation() {
    return _creation;
}

void Order::setSent(Date sent) {
    _sent = sent;
}

Date Order::getSent() {
    return _sent;
}

void Order::setType(char type) {
    _type = type;
}

char Order::getType() {
    return _type;
}

void Order::setUserId(unsigned int user_id) {
    _user_id = user_id;
}

unsigned int Order::getUserId() {
    return _user_id;
}

void Order::OrderCheckbook() {

}

void Order::OrderCreditCard() {

}

bool Order::save() {
    return true;
}