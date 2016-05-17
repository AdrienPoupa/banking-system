#include <iostream>
#include "src/Address.h"
#include "src/User.h"
#include "src/Bank.h"
#include "src/BankAccount.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

   //test->getBankAccounts();
    Bank* bank = Bank::getSingleton();
    bank->run();

    return 0;
}