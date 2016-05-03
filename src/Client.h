/**
 * Project Untitled
 */


#ifndef _CLIENT_H
#define _CLIENT_H

#include "User.h"


class Client: public User {
public:

    void ContactAdvisor();

    void LoanApplication();
};

#endif //_CLIENT_H
