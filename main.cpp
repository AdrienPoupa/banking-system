#include <iostream>
#include "src/Address.h"
#include "src/User.h"
#include "src/Bank.h"
#include "src/Client.h"

using namespace std;

int main() {
    User *user = new Client("John","Doe");
    user->save();
    Bank* bank = Bank::getSingleton();
    bank->run();

    return 0;
}