/**
 * Project Untitled
 */


#ifndef _BANKACCOUNT_H
#define _BANKACCOUNT_H

class BankAccount {
public: 
    char swift;
    
    void ConsultAmount();
    
    void Transfer();
    
    void ConsultHistory();
    
    void RequestSwift();
};

#endif //_BANK ACCOUNT_H