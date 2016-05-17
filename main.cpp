#include <iostream>
#include "src/Address.h"
#include "src/User.h"
#include "src/Bank.h"
#include "src/Client.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Address* address = new Address(1, "Test", "67000", "Test", "Malaysia");
    cout << *address << endl;


    Bank* bank = Bank::getSingleton();
    bank->run();

    return 0;
}