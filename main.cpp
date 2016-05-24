#include <iostream>
#include "src/Bank.h"
#include "src/Date.h"

using namespace std;

int main() {
    try {
        Bank *bank = Bank::getSingleton();
        bank->run();
    }
    catch (const exception& e)  {
        cout << e.what() << endl;
    }
    return 0;
}