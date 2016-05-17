#include <iostream>
#include "src/Address.h"
#include "src/User.h"
#include "src/Bank.h"
#include "src/Administrator.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Address* address = new Address(1, "Test", "67000", "Test", "Malaysia");
    cout << *address << endl;

    User* user = new Administrator("Adrien", "Le Roy");
    user->save();
    User* test = new Administrator(1);
    cout << *test << endl;
    Bank* bank = Bank::getSingleton();
    bank->run();
    return 0;
}