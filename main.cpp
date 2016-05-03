#include <iostream>
#include "src/Address.h"
#include "src/User.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Address* address = new Address(1, "Test", "67000", "Test", "Malaysia");
    cout << *address << endl;

    User* user = new User("Adrien", "Le Roy");
    cout << *user << endl;

    return 0;
}