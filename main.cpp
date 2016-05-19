#include <iostream>
#include "src/Bank.h"
#include "src/Date.h"

using namespace std;

int main() {
   /* Bank* bank = Bank::getSingleton();
    bank->run();*/
Date* d = new Date();
cout << *d;
    return 0;
}