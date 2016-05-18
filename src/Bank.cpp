#include "Bank.h"

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

    int idToOpen;
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

            for(unsigned int i = 0; i < (11 - users[i]["id"].length()); i++){
                space += " ";
            }
            if (users[i]["isadmin"] == "1")
            {
                star = "**";
            }
            if(users[i]["isadvisor"] == "1"){
                star = "*";
            }

            cout << space<< users[i]["id"] << " | " << star << users[i]["name"] << " " << users[i]["surname"] << endl;
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
    //User accountToOpen;
    if(stoi(users[correctId]["isadvisor"]) == 1){
        Advisor accountToOpen(idToOpen);
        _currentUser=accountToOpen;
    }
    else if(stoi(users[correctId]["isadmin"]) == 1){
        Administrator accountToOpen(idToOpen);
        _currentUser=accountToOpen;
    }
    else{
        Client accountToOpen(idToOpen);
        _currentUser=accountToOpen;
    }


    int essai = 3;
    while(!correctPass && essai > 0)
    {
        cout << "Password: " << endl;
        string inputPassword;
        cin >> inputPassword;
        if (sha256(inputPassword) == _currentUser.getPassword())
        {
            correctPass = true;
        }
        _currentUser.checkPassword(inputPassword);
        essai--;

        if (correctPass)
        {
            cout << "Authentication successful ! " << endl << endl;
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
        cout << "#  -- Main menu --           #" << endl;
        cout << "#  1. Consult bank account   #" << endl;
        cout << "#  2. Transfer               #" << endl;
        cout << "#  3. Liste des cds          #" << endl;
        cout << "#  4. Liste des artistes     #" << endl;
        cout << "#  5. Mes emprunts           #" << endl;
        cout << "#  6. Chercher un article    #" << endl;

        if (isAdmin())
        {
            cout << "#                            #" << endl;
            cout << "# -- Menu Administrateur --  #" << endl;
            cout << "#  7. Liste des utilisateurs #" << endl;
            cout << "#  8. Liste des genres       #" << endl;
            cout << "#  9. Liste des statuts      #" << endl;
            cout << "# 10. Liste des emprunts     #" << endl;
            cout << "# 11. Ajouter un utilisateur #" << endl;
            cout << "# 12. Ajouter un livre       #" << endl;
            cout << "# 13. Ajouter un cd          #" << endl;
            cout << "# 14. Ajouter un dvd         #" << endl;
            cout << "# 15. Ajouter un artiste     #" << endl;
            cout << "# 16. Ajouter un genre       #" << endl;
            cout << "# 17. Ajouter un statuts     #" << endl;
            cout << "# 18. Ajouter un emprunt     #" << endl;
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

    } while(failInput || choice < 0 || (!isAdmin() && choice > 6) || choice > 18);

    return choice;
}

void Bank::redirectChoice(const int choice)
{
    switch (choice)
    {
        // User action
        case 0:
            return;
            break;
             case 1:
                if(_currentUser.isAdvisor()){
                    Advisor advisor= Advisor(_currentUser.getId());
                    advisor.getUserBankAccounts();
                 }
            else if(!_currentUser.isAdvisor() && !_currentUser.isAdmin()){
                    Client client= Client(_currentUser.getId());
                    client.getBankAccounts();
                }
                 break;

             case 2:
                 if(_currentUser.isAdvisor()){
                     Advisor advisor= Advisor(_currentUser.getId());
                     advisor.TransferMoneyUser();
                 }
                 else if(!_currentUser.isAdvisor() && !_currentUser.isAdmin()){
                     Client client= Client(_currentUser.getId());
                     client.Transfer();
                 }
                 break;
            /*
             case 3:
                 getListEntity<Cd>();
                 break;
             case 4:
                 getListEntity<Artist>();
                 break;
             case 5:
                 borrowedMenu();
                 break;
             case 6:
                 searchList();
                 break;
                 // Admin action
             case 7:
                 getListEntity<User>();
                 break;
             case 8:
                 getListEntity<Genre>();
                 break;
             case 9:
                 getListEntity<Status>();
                 break;
             case 10:
                 getListEntity<Transaction>();
                 break;
             case 11:
                 addThing<User>();
                 break;
             case 12:
                 addThing<Book>();
                 break;
             case 13:
                 addThing<Cd>();
                 break;
             case 14:
                 addThing<Dvd>();
                 break;
             case 15:
                 addThing<Artist>();
                 break;
             case 16:
                 addThing<Genre>();
                 break;
             case 17:
                 addThing<Status>();
                 break;
             case 18:
                 addThing<Transaction>();
                 break;
             default:
                 return;
                 break;*/
         }
}
