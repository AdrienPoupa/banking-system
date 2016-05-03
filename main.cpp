#include <iostream>
#include "src/Address.h"
#include "src/User.h"

using namespace std;

int main() {
    User *user = new User("Adrien", "Le Roy");
    cout << *user << endl;

    return 0;
}