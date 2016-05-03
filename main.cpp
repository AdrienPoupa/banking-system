#include <iostream>
#include "src/Address.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Address* address = new Address(1, "Test", "67000", "Test", "Malaysia");
    cout << *address << endl;

    return 0;
}