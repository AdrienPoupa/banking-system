#include "Bank.h"
#include "Transaction.h"
#include "Order.h"

using namespace std;

class NoDbException: public exception
{
    virtual const char* what() const throw()
    {
        return "The file bank.db3 isn't available.";
    }
} NoDb;

Bank* Bank::singleton = NULL;

Bank* Bank::getSingleton()
{
    if (singleton == NULL)
    {
        // check if bank.db3 exist
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
    return _currentUser.isAdmin();
}

bool Bank::isAdvisor()
{
    return _currentUser.isAdvisor();
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

        cout << endl << "ID : " << endl;
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
        Advisor accountToOpen(idToOpen);
        _currentUser = accountToOpen;
    }
    else if(stoi(users[correctId]["isadmin"]) == 1){
        Administrator accountToOpen(idToOpen);
        _currentUser = accountToOpen;
    }
    else{
        Client accountToOpen(idToOpen);
        _currentUser = accountToOpen;
    }


    int essai = 3;
    while(!correctPass && essai > 0)
    {
        cout << "Password: " << endl;
        string inputPassword;
        cin >> inputPassword;
        correctPass = _currentUser.checkPassword(inputPassword);
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
            cout << "#  6. Consult messages       #" << endl;
            cout << "#  8. Add a transaction      #" << endl;
            cout << "#  9. Add a client           #" << endl;
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
                Advisor advisor = Advisor(_currentUser.getId());
                advisor.getUserBankAccounts();
             }
        else if(!isAdvisor() && !isAdmin()){
                Client client = Client(_currentUser.getId());
                client.getBankAccounts();
            }
             break;

         case 2:
             if(isAdvisor()){
                 Advisor advisor = Advisor(_currentUser.getId());
                 advisor.TransferMoneyUser();
             }
             else if(!isAdvisor() && !isAdmin()){
                 Client client = Client(_currentUser.getId());
                 client.Transfer();
             }
             break;

        case 3:
            char newPassword[256];
            cout << "New password: " << endl;
            cin.ignore(1, '\n');
            cin.getline(newPassword, '\n');
            _currentUser.setPassword(newPassword);
            _currentUser.save();
            break;

         case 4:
             if(isAdvisor()){
                 Advisor advisor = Advisor(_currentUser.getId());
                 advisor.ConsultMessages();
             }
             else if(!isAdvisor() && !isAdmin()){
                 Client client = Client(_currentUser.getId());
                 client.contactAdvisor();
             }
             break;

        // Expense history
        case 5: {
            Client client = Client(_currentUser.getId());
            set<int> accounts = client.getAccountsIds();

            for(auto i : accounts) {
                BankAccount* account = new BankAccount(i);
                account->ConsultHistory();
            }

            break;
        }

        case 6:{
            if(isAdvisor()){
                Advisor advisor = Advisor(_currentUser.getId());
                advisor.ConsultMessages();
            }
            break;
        }

        // Order a checkbook
        case 6: {
            Client client = Client(_currentUser.getId());

            cout << "Available accounts:" << endl;
            Client client2 = Client(_currentUser.getId());

            BankAccount* toOpen = client2.getBankAccounts();

            Order* order = new Order();
            Date* today = new Date();
            Date* sent = new Date(-1, -1, -1);
            order->setCreation(*today);
            order->setSent(*sent);
            order->setClient(client);
            order->setType(0);
            order->setAccount(*toOpen);
            order->save();

            cout << "Credit checkbook" << endl;

            break;
        }

        // Order a credit card
        case 7: {
            Client client = Client(_currentUser.getId());

            cout << "Available accounts:" << endl;
            Client client2 = Client(_currentUser.getId());

            BankAccount* toOpen = client2.getBankAccounts();

            Order* order = new Order();
            Date* today = new Date();
            Date* sent = new Date(-1, -1, -1);
            order->setCreation(*today);
            order->setSent(*sent);
            order->setClient(client);
            order->setType(1);
            order->setAccount(*toOpen);
            order->save();

            cout << "Credit card ordered" << endl;

            break;
        }

        // Add a transaction
        case 8: {
            cout << "Available accounts:" << endl;
            Client client2 = Client(_currentUser.getId());

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

         default:
             return;
    }
}
