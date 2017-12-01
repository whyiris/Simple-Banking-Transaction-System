//---------------------------------------------------------------------------
// clientData.cpp
// clientData for one client
// each client has last name, first name, account number
// each client has ten Account object which store in an array
// each client has clientHistory which use vector to represent
// 
// in this class,
// operator ==, !=, <, >, are overload 
// by using accountNumber to determine the result
// Also, output operator is overload to display report for client

#include "clientData.h"
#include "Transaction.h"
using namespace std;

// default constructor
clientData::clientData() {
    lastName = "";
    firstName = "";
    accountNumber = 0;
}

//----------------------------------------------------------------------------
// Constructor
// used as a fake constructor in transaction class
// when needed to retrieve a client
clientData::clientData(int number) {
    accountNumber = number;
    lastName = "";
    firstName = "";
    // required to create account for client
    // since destructor will delete the account
    // if there is no account, 
    // the number of allocation and delete will not match 
    for (int i = 0; i < 10; i++) {
        acctptr[i] = new Account(i);
    }
}

//----------------------------------------------------------------------------
// Destructor
clientData::~clientData() {
    // deallocate the memory for account
    for (int i = 0; i<10; i++){
        delete acctptr[i];
    }
    // deallocate the clientHistory
    for (size_t n = 0; n < clientHistory.size(); n++)
        delete clientHistory[n];

}

//----------------------------------------------------------------------------
// setData
// set client data when read the client data file to create client object
// Format looks like this:
// duck daffy  5555  4500  500  0   0   0   0   0   0   0    0
// lastName 
// firstName 
// accountNumber 
// balance for ten different accounts
bool clientData::setData(istream & infile) {
    // get the lastName, firstName, and accountNumber from datafile
    infile >> lastName >> firstName >> accountNumber;
    
    // create ten Account objects for each client 
    for (int i = 0; i < 10; i++) {
        int balance;
        // get the balance from datafile
        infile >> balance;
        acctptr[i] = new Account(i, balance);
    }
    return true;
}

//----------------------------------------------------------------------------
// overload operator==
// compare for equal of 2 ClientDatas by using the accountNumber
bool clientData::operator==(const clientData & client) const{
    return accountNumber == client.accountNumber;
}

//----------------------------------------------------------------------------
// overload operator!=
// compare not equal of 2 ClientDatas by using the accountNumber
bool clientData::operator!=(const clientData & client) const {
    return accountNumber != client.accountNumber;
}

//----------------------------------------------------------------------------
// overload operator<
// true if client object is < parameter by using the accountNumber, 
// otherwise false
bool clientData::operator<(const clientData & client) const {
    return accountNumber < client.accountNumber;
}

//----------------------------------------------------------------------------
// overload operator>
// true if current object is > parameter by using the accountNumber,
// otherwise false
bool clientData::operator>(const clientData & client) const {
    return accountNumber > client.accountNumber;
}

//----------------------------------------------------------------------------
// getLastName
// get the last name of client
string clientData::getLastName() const {
    return lastName;
}

//----------------------------------------------------------------------------
// getFirstName
// get the first name of client
string clientData::getFirstName() const {
    return firstName;
}

//----------------------------------------------------------------------------
// getAccountNumber
// get the account of client
int clientData::getAccountNumber() const {
    return accountNumber;
}

//----------------------------------------------------------------------------
// getAccount
// get a specific account of client
Account* clientData::getAccount(int i) {
    return acctptr[i];
}

//----------------------------------------------------------------------------
// setClientHistory
// set the clientHistory vector for the client
void clientData::setClientHistory(Transaction*& t) {
    clientHistory.push_back(t);
}

//----------------------------------------------------------------------------
// getClientHistory
// get the clientHistory vector for the client
vector<Transaction*> clientData::getClientHistory() {
    return clientHistory;
}

//---------------------------------------------------------------------------
// operator<<
// Overloaded output operator for class clientData
ostream & operator<<(ostream & output, const clientData & client) {

    // display the client object with designed format
    output << client.getAccountNumber()<<"  " ;
    output << client.getFirstName() <<" "<< client.getLastName() << endl;
    output << "Initial Balance: ";
    
    // display the initial account balance
    for (int i = 0; i < 10; i++) {
        output << *client.acctptr[i];
    }
    output << endl;

    output << "Final Balance:   ";
    // display the finial account balance
    for (int i = 0; i < 10; i++) {
        (*client.acctptr[i]).displayFinalBalance();
    }
    output << endl;

    return output;
}
