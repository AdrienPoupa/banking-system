/**
 * Project Untitled
 */


#include "Loan.h"

/**
 * Loan implementation
 */

Loan::Loan(const Date creation, const Date validation, const User sender) : _creation(creation), _validation(validation),
                                                                      _sender(sender) { }


unsigned int Loan::getId() const {
    return _id;
}

void Loan::setCreation(Date creation) {
    _creation = creation;
}

Date Loan::getCreation() {
    return _creation;
}

void Loan::setValidation(Date validation) {
    _validation = validation;
}

Date Loan::getValidation() {
    return _validation;
}

void Loan::validate() {

}

void Loan::decline() {

}