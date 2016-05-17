#ifndef Bank_h
#define Bank_h

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <set>


#ifdef _WIN32
#define CLEAN_SCREEN "CLS"
#include "mingw.thread.h"
#else
#define CLEAN_SCREEN "clear"
#include <thread>
#endif

#include "BaseModel.h"
#include "User.h"
#include "../sqlite/SQLiteCpp.h"

class Bank {
    User _currentUser;

    public:
        static Bank *getSingleton();
        ~Bank();

        void run();

    private:
        Bank();

        bool isAdmin();

        bool connect();

        int displayMenu();
        void redirectChoice(const int choice);
    static Bank* singleton;
};


#endif /* Bank_h */