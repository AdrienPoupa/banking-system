/**
 * Project Untitled
 */


#include "BankAccount.h"

using namespace std;

/**
 * BankAccount implementation
 */

BankAccount::BankAccount(unsigned int user_id, const string swift, const string bic) :_user_id(user_id),
                                                                                         _swift(swift),
                                                                                         _bic(bic) { }

unsigned int BankAccount::getId() {
    return _id;
}

void BankAccount::setUserId(unsigned int user_id) {
    _user_id = user_id;
}

unsigned int BankAccount::getUserId() {
    return _user_id;
}

void BankAccount::setBic(std::string bic) {
    _bic = bic;
}

std::string BankAccount::getBic() {
    return _bic;
}

void BankAccount::setSwift(std::string swift) {
    _swift = swift;
}

std::string BankAccount::getSwift() {
    return _swift;
}

void BankAccount::ConsultAmount() {

}

void BankAccount::Transfer() {

}

void BankAccount::ConsultHistory() {

}

void BankAccount::RequestSwift() {

}

