#include <iostream>
#include "src/Bank.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

int main() {
   /* Bank* bank = Bank::getSingleton();
    bank->run();*/
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
    std::string str(buffer);

    std::cout << str;

    return 0;
}