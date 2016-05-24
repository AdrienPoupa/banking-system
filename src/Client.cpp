/**
 * Project Untitled
 */

#include "Client.h"
#include "Notification.h"

using namespace std;

/**
 * Client implementation
 */


Client::Client(const unsigned int id) // Get a Client from an ID provided by DB
{
    map<string, string> data = BaseModel::getById(_dbTable, id);

    if (!data.empty())
    {
        _id = id;
        _firstName = data["name"];
        _lastName = data["surname"];
        _birthDate = Date(data["birthdate"]);
        _phone = data["phone"];
        _address = Address(stoi(data["house_number"]), data["street"], data["postal_code"], data["town"], data["country"]);
        _isAdmin = stoi(data["isadmin"]);
        _isAdvisor = stoi(data["isadvisor"]);
        _password = data["password"];
        _idAdvisor = stoi(data["id_advisor"]);
    }
    else
    {
        throw invalid_argument("Please enter a valid ID");
    }
}
/*
Client::~Client()
{

}*/
BankAccount* Client::getBankAccounts() {
    map<int, map<string, string>> bankAccount = BaseModel::select("bank_account", "id, swift, BIC, id_user, balance",
                                                                  "id_user = " + to_string(getId()));

    int totalAccount = (int)bankAccount.size();

    int idToOpen;
    set<int> AccountIds = set<int>();
    bool correctId = false;

    do{
        cout << "-------------------------------------------------------" << endl;
        cout << " -- Account's list of "<< getLastName() << " " << getFirstName() <<" --" << endl;
        cout << " ID |       SWIFT       |     BIC     " << endl;
        cout << "----|-------------------|--------------" << endl;
        for (int i = 1; i != totalAccount + 1; i++)
        {
                cout << bankAccount[i]["id"] << "     " << bankAccount[i]["SWIFT"] << "          " <<
                bankAccount[i]["BIC"] << endl;
                AccountIds.insert(stoi(bankAccount[i]["id"]));
        }

        cout << endl << "Bank account's id : " << endl;
        cin >> idToOpen;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            correctId = AccountIds.find(idToOpen) != AccountIds.end();
        }

        if (!correctId)
        {
            cout << "Unknown ID ..." << endl;
        }

    } while(!correctId);
    BankAccount *bc = new BankAccount(idToOpen);
    cout << *bc << endl;
    return bc;
}

set<int> Client::getAccountsIds() {
    map<int, map<string, string>> bankAccount = BaseModel::select("bank_account", "id", "id_user=" + to_string(_id));

    int totalAccount = (int)bankAccount.size();

    set<int> AccountIds = set<int>();

    for (int i = 1; i != totalAccount + 1; i++)
    {
        AccountIds.insert(stoi(bankAccount[i]["id"]));
    }

    return AccountIds;
}

Client::Client(const std::string lastName, const std::string firstName, const std::string password) {
    _lastName = lastName;
    _firstName = firstName;
    _password = sha256(password);
}

void Client::Transfer(){
    int amountToTransfer;
    BankAccount* bcIncome = getBankAccounts();
    cout << endl << "Amount to transfer : " << endl;
    cin >> amountToTransfer;

    if(bcIncome->ConsultAmount()< amountToTransfer){
        cout << "Insufficient amount" << endl;
    }
    else{
        BankAccount* bcToTransfer = getBankAccounts();
        if(bcToTransfer->getId() != bcIncome->getId()) {
            bcIncome->Transfer(amountToTransfer, bcToTransfer);
            cout << *bcIncome << endl;
        }
        else{
            cout << "The two accounts must be different"<<endl;
        }
    }
}

Client::Client(const std::string lastName, const std::string firstName, const Date birthDate){
    _lastName = lastName;
    _firstName = firstName;
    _birthDate = birthDate;
}

void Client::setAdvisor(int idAdvisor) {
    _idAdvisor = idAdvisor;
}

int Client::getAdvisor() {
    return _idAdvisor;
}

void Client::contactAdvisor() {
    string message;
    Advisor *advisor = new Advisor((unsigned) this->_idAdvisor);
    cout << "You are going to send a message to: " << advisor->getLastName() << " " << advisor->getFirstName() << endl;
    cout << "Enter the message you want to send." << endl;
    cin.ignore();
    getline(cin, message);
    if(message != ""){
        Contact* contact = new Contact(this->_id, (unsigned) this->_idAdvisor, message);
        contact->save();
        cout << "Your message has been sent" << endl;

        // Add a new notification to the advisor
        string notificationMessage = "New message from " + this->getLastName() + " " + this->getFirstName() + " : " + message;
        Notification* notification = new Notification(notificationMessage, (unsigned) this->_idAdvisor);
        notification->save();
    }
    else{
        cout << "You cannot send an empty message." << endl;
    }
}
void Client::LoanApplication() {

}