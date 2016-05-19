#include <iostream>
#include "src/Bank.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

int main() {
    try
    {
        Bank* bank = Bank::getSingleton();

        bank->run();

        delete bank;
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}