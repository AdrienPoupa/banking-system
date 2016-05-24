#include "Bank.h"
#include "Transaction.h"
#include "Order.h"
#include "Notification.h"
#include "Loan.h"

using namespace std;

class NoDbException: public exception
{
    virtual const char* what() const throw()
    {
        return "The file bank.db3 is not available.";
    }
} NoDb;

Bank* Bank::singleton = NULL;

Bank* Bank::getSingleton()
{
    if (singleton == NULL)
    {
        // check if bank.db3 exists
        ifstream mfile("bank.db3");
        if (mfile)
        {
            singleton = new Bank();
            mfile.close();
        }
        else
        {
            throw NoDb;
        }
    }

    return singleton;
}

Bank::Bank()
{
    cout << "######################################" << endl;
    cout << "#                                    #" << endl;
    cout << "#  Welcome to our Banking System !   #" << endl;
    cout << "#                                    #" << endl;
    cout << "#  Made by:                          #" << endl;
    cout << "#          - Andres Viso             #" << endl;
    cout << "#          - Adrien Poupa            #" << endl;
    cout << "#          - Adrien Le Roy           #" << endl;
    cout << "#                                    #" << endl;
    cout << "#             Group 1                #" << endl;
    cout << "#                                    #" << endl;
    cout << "######################################" << endl;
    cout << endl;
}

Bank::~Bank()
{
    singleton = NULL;
}

bool Bank::isAdmin()
{
    return _currentUser->isAdmin();
}

bool Bank::isAdvisor()
{
    return _currentUser->isAdvisor();
}

void Bank::run()
{
    cout << endl << "Loading... (2 sec)" << endl;
    std::this_thread::sleep_for(chrono::seconds(2));

    // connection
    bool connected = connect();

    if (!connected)
    {
        cout << "Authentication failed." << endl;
        return;
    }
    bool quit = false;

    while(!quit)
    {
        int choice = displayMenu();
        if (choice)
            redirectChoice(choice);
        else
            quit = true;
    }

    cout << "See you soon!" << endl;
}

bool Bank::connect()
{
    map<int, map<string, string>> users = BaseModel::select("users", "id, name, surname, isadmin, isadvisor");

    int totalUsers = (int)users.size();

    unsigned int idToOpen;
    set<int> userIds = set<int>();
    bool correctId = false;
    bool correctPass = false;
    do{
        cout << "-------------------------------------------------------" << endl;
        cout << " -- Account list for connection--" << endl;
        cout << " -- * -> Advisor --" << endl;
        cout << " -- ** -> Admin --" << endl;
        cout << "     ID      | Last name First name " << endl;
        cout << "-------------|---------------------" << endl;
        for (int i = 1; i != totalUsers + 1; i++)
        {
            string space, star = "";

            int spaceNumber;

            if (stoi(users[i]["id"]) < 10) {
                spaceNumber = 11;

            }
            else {
                spaceNumber = 10;
            }

            for(unsigned int i = 0; i < (spaceNumber - users[i]["id"].length()); i++){
                space += " ";
            }

            if (users[i]["isadmin"] == "1")
            {
                star = "**";
            }
            if(users[i]["isadvisor"] == "1"){
                star = "*";
            }

            cout << space << users[i]["id"] << " | " << star << users[i]["name"] << " " << users[i]["surname"] << endl;
            userIds.insert(stoi(users[i]["id"]));
        }

        cout << endl << "ID: " << endl;
        cin >> idToOpen;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            correctId = userIds.find(idToOpen) != userIds.end();
        }

        if (!correctId)
        {
            cout << "Unknown ID ..." << endl;
        }

    } while(!correctId);

    if(stoi(users[correctId]["isadvisor"]) == 1){
        Advisor* accountToOpen = new Advisor(idToOpen);
        _currentUser = accountToOpen;
    }
    else if(stoi(users[correctId]["isadmin"]) == 1){
        Administrator* accountToOpen = new Administrator(idToOpen);
        _currentUser = accountToOpen;
    }
    else{
        Client* accountToOpen = new Client(idToOpen);
        _currentUser = accountToOpen;
    }


    int essai = 3;
    while(!correctPass && essai > 0)
    {
        cout << "Password: " << endl;
        string inputPassword;
        cin >> inputPassword;
        correctPass = _currentUser->checkPassword(inputPassword);
        essai--;

        if (correctPass)
        {
            cout << "Authentication successful! " << endl << endl;
        }
        else
        {
            cout << "Wrong password" << endl;
        }
    }
    return correctPass;
}

int Bank::displayMenu()
{
    int choice;
    bool failInput = false;
    do
    {
        map<int, map<string, string>> notifications = BaseModel::select("notifications", "id, message, read",
                                                      "userid = " + to_string(_currentUser->getId()) + " AND read = 0");

        int totalNotifications = (int)notifications.size();

        if (totalNotifications > 0) {
            cout << endl;
            cout << "##############################" << endl;
            cout << "#                            #" << endl;
            cout << "#  --- New Notifications --- #" << endl;
            cout << "#                            #" << endl;
            cout << "##############################" << endl;

            for (int i = 1; i != totalNotifications + 1; i++)
            {
                cout << i << ". " << notifications[i]["message"] << endl;
                Notification* toBeRead = new Notification((unsigned) stoi(notifications[i]["id"]));
                toBeRead->setRead(true);
                toBeRead->save();
            }
        }

        cout << endl;
        cout << "##############################" << endl;
        cout << "#                            #" << endl;
        cout << "#  ------- Main menu ------- #" << endl;
        cout << "#  1. Consult bank account   #" << endl;
        cout << "#  2. Transfer               #" << endl;
        cout << "#  3. Change password        #" << endl;

        if (isAdmin())
        {
            cout << "#                            #" << endl;
            cout << "# ------- Admin Menu ------- #" << endl;
            cout << "#  10. Add an advisor        #" << endl;
        }
        else if (isAdvisor())
        {
            cout << "#                            #" << endl;
            cout << "# ------ Advisor Menu ------ #" << endl;
            cout << "#  4. Consult messages       #" << endl;
            cout << "#  8. Add a transaction      #" << endl;
            cout << "#  9. Add a client           #" << endl;
            cout << "#  10. Create a bank account #" << endl;
            cout << "#  11. Close a bank account  #" << endl;
            cout << "#  13. Handle loans          #" << endl;
        }
        else
        {
            cout << "#                            #" << endl;
            cout << "# ------ Client Menu ------- #" << endl;
            cout << "#  4. Contact advisor        #" << endl;
            cout << "#  5. Expense history        #" << endl;
            cout << "#  6. Order a checkbook      #" << endl;
            cout << "#  7. Order a credit card    #" << endl;
            cout << "#  8. Add a transaction      #" << endl;
            cout << "#  12. Loan application      #" << endl;
        }

        cout << "#  -----------------------   #" << endl;
        cout << "#  0. Cancel                 #" << endl;
        cout << "##############################" << endl;

        cout << "\tChoice: " << endl;
        cin >> choice;
        if(cin.fail()){
            failInput = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    //} while(failInput || choice < 0 || (!isAdmin() && choice > 6) || choice > 18); todo: permissions
    } while(failInput || choice < 0);

    return choice;
}

void Bank::redirectChoice(const int choice)
{
    switch (choice)
    {
    // User action
        case 1:
            if(isAdvisor()){
                Advisor advisor = Advisor(_currentUser->getId());
                advisor.getUserBankAccounts();
             }
        else if(!isAdvisor() && !isAdmin()){
                Client client = Client(_currentUser->getId());
                client.getBankAccounts();
            }
             break;

         case 2:
             if(isAdvisor()){
                 Advisor advisor = Advisor(_currentUser->getId());
                 advisor.TransferMoneyUser();
             }
             else if(!isAdvisor() && !isAdmin()){
                 Client client = Client(_currentUser->getId());
                 client.Transfer();
             }
             break;

        case 3:
            char newPassword[256];
            cout << "New password: " << endl;
            cin.ignore(1, '\n');
            cin.getline(newPassword, '\n');
            _currentUser->setPassword(newPassword);
            _currentUser->save();
            break;

         case 4:
             if(isAdvisor()){
                 Advisor advisor = Advisor(_currentUser->getId());
                 advisor.ConsultMessages();
             }
             else if(!isAdvisor() && !isAdmin()){
                 Client client = Client(_currentUser->getId());
                 client.contactAdvisor();
             }
             break;

        // Expense history
        case 5: {
            Client client = Client(_currentUser->getId());
            set<int> accounts = client.getAccountsIds();

            for(auto i : accounts) {
                BankAccount* account = new BankAccount(i);
                account->ConsultHistory();
            }

            break;
        }


        // Order a checkbook
        case 6: {
            Client client = Client(_currentUser->getId());

            cout << "Available accounts:" << endl;
            Client client2 = Client(_currentUser->getId());

            BankAccount* toOpen = client2.getBankAccounts();

            Order* order = new Order();
            order->setClient(client);
            order->setAccount(*toOpen);
            order->OrderCheckbook();

            cout << "Checkbook ordered" << endl;

            break;
        }

        // Order a credit card
        case 7: {
            Client client = Client(_currentUser->getId());

            cout << "Available accounts:" << endl;
            Client client2 = Client(_currentUser->getId());

            BankAccount* toOpen = client2.getBankAccounts();

            Order* order = new Order();
            order->setClient(client);
            order->setAccount(*toOpen);
            order->OrderCreditCard();

            cout << "Credit card ordered" << endl;

            break;
        }

        // Add a transaction
        case 8: {
            cout << "Available accounts:" << endl;
            Client client2 = Client(_currentUser->getId());

            BankAccount* toOpen = client2.getBankAccounts();

            Transaction* transaction2 = new Transaction();
            transaction2->setBankAccount(*toOpen);

            Date transactionDate;
            int amount;
            char description[256];

            cout << "Date: " << endl;
            cin >> transactionDate;
            transaction2->setDate(transactionDate);
            cout << "Amount: " << endl;
            cin >> amount;
            transaction2->setAmount(amount);
            cout << "Description: " << endl;
            cin.ignore(1, '\n');
            cin.getline(description, '\n');
            transaction2->setDescription(description);

            transaction2->save();
            break;
        }

        // Make a loan application
        case 12: {
            Client client3 = Client(_currentUser->getId());

            Loan* loanApplication = new Loan();
            loanApplication->setSender(_currentUser);
            loanApplication->setAdvisor(client3.getAdvisor());
            cin >> *loanApplication;

            loanApplication->save();

            // Notify the advisor
            string notificationMessage = "New loan inquiry for " + to_string(loanApplication->getAmount()) + " from "
                                         + _currentUser->getLastName() + " " + _currentUser->getFirstName();
            Notification* notification = new Notification(notificationMessage, (unsigned) client3.getAdvisor());
            notification->save();

            break;
        }

        // Handle loans
        case 13: {
            cout << "Loans awaiting your approval:" << endl;

            map<int, map<string, string>> loans = BaseModel::select("loans", "id, creation, validation, sender, approved, amount",
                                                                            "advisor_id = " + to_string(_currentUser->getId()) + " AND validation = '0001-01-01'");

            int totalLoans = (int)loans.size();

            if (totalLoans > 0) {
                cout << endl;
                cout << "##############################" << endl;
                cout << "#                            #" << endl;
                cout << "#  --------- Loans --------- #" << endl;
                cout << "#                            #" << endl;
                cout << "##############################" << endl;

                for (int i = 1; i != totalLoans + 1; i++)
                {
                    Client* sender = new Client((unsigned) stoi(loans[i]["sender"]));
                    cout << loans[i]["id"] << ". " << loans[i]["amount"] << " by " << sender->getFirstName() << " " << sender->getLastName() << endl;
                }

                cout << "Which loan do you want to take care of?" << endl;
                int loanId, choiceLoan;
                cin >> loanId;

                Loan* loanToHandle = new Loan((unsigned) loanId);

                cout << "If you accept this loan, type 1, otherwise type 0" << endl;
                cin >> choiceLoan;

                if (choiceLoan == 1) {
                    loanToHandle->validate();
                    loanToHandle->save();
                    cout << "Loan validated" << endl;
                }
                else {
                    loanToHandle->decline();
                    loanToHandle->save();
                    cout << "Loan declined" << endl;
                }
            }
            else {
                cout << "No loans awaiting your approval." << endl;
            }

            break;
        }

        // Add a bank account
        case 10: {

            if(isAdvisor()){
                BankAccount* newbankaccount = new BankAccount();

                int userIDD;
                std::string swift2;
                std::string bic2;
                int balance2;

                newbankaccount->getusersIDS();

                cout << "UserId: " << endl;
                cin >> userIDD;
                newbankaccount->setUserId((unsigned) userIDD);
                cout << "Swift: " << endl;
                cin >> swift2;
                newbankaccount->setSwift(swift2);
                cout << "BIC: " << endl;
                cin >> bic2;
                newbankaccount->setBic(bic2);
                cout << "Balance: " << endl;
                cin >> balance2;
                newbankaccount->setBalance(balance2);

                newbankaccount->save();
            }
            else
            {
                cout << "You are not allowed to perform this action" << endl;
            }

            break;
        }

        case 11: {

            if(isAdvisor()){

                BankAccount* newbankaccount = new BankAccount();

                int userIDD;
                int id_;

                newbankaccount->getusersIDS();

                cout << "Choose the client that you want to close an account by putting the IDuser: " << endl;
                cin >> userIDD;

                Client client2 = Client((unsigned) userIDD);

                BankAccount* toOpen = client2.getBankAccounts();

                cout << "Choose the account that you want to close by putting the ID" << endl;
                cin >>id_;

                BankAccount suppr = BankAccount(id_);
                suppr.remove();

            }
            else
            {
                cout << "You are not allowed to perform this action" << endl;
            }

            break;
        }

         default:
             return;
    }
}
