//---------------------------------------------------------------------------
// clientData.h 
// clientData for one client
// each client has last name, first name, account number
// each client has ten Account object which store in an array
// each client has clientHistory which use vector to represent
// 
// in this class,
// operator ==, !=, <, >, are overload 
// by using accountNumber to determine the result
// Also, output operator is overload to display report for client
// 

#ifndef clientdata_h
#define clientdata_h
#include "Account.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//---------------------------------------------------------------------------
class Transaction;
class clientData {

//---------------------------------------------------------------------------
// operator<<
// Overloaded output operator for class clientData
    friend ostream& operator<<(ostream &, const clientData &);
public:

//----------------------------------------------------------------------------
// Default Constructor
    clientData();

//----------------------------------------------------------------------------
// Constructor
// used as a fake constructor in transaction class
// when needed to retrieve a client
    clientData(int);

//----------------------------------------------------------------------------
// Destructor
    ~clientData();

//----------------------------------------------------------------------------
// setData
// set client data when read the client data file to create client object
// Format looks like this:
// duck daffy  5555  4500  500  0   0   0   0   0   0   0    0
// firstName 
// lastName 
// accountNumber 
// balance for ten different accounts
    bool setData(istream& infile);

//----------------------------------------------------------------------------
// overload operator==
// compare for equal of 2 ClientDatas by using the accountNumber
    bool operator==(const clientData &) const;

//----------------------------------------------------------------------------
// overload operator!=
// compare not equal of 2 ClientDatas by using the accountNumber
    bool operator!=(const clientData &) const;

//----------------------------------------------------------------------------
// overload operator<
// true if client object is < parameter by using the accountNumber, 
// otherwise false
    bool operator<(const clientData &) const;

//----------------------------------------------------------------------------
// overload operator>
// true if current object is > parameter by using the accountNumber,
// otherwise false
    bool operator>(const clientData &) const;

//----------------------------------------------------------------------------
// getLastName
// get the last name of client
    string getLastName() const;

//----------------------------------------------------------------------------
// getFirstName
// get the first name of client
    string getFirstName() const;

//----------------------------------------------------------------------------
// getAccountNumber
// get the account of client
    int getAccountNumber() const;

//----------------------------------------------------------------------------
// getAccount
// get a specific account of client
    Account* getAccount(int i);

//----------------------------------------------------------------------------
// setClientHistory
// set the clientHistory vector for the client
    void setClientHistory(Transaction*&);

//----------------------------------------------------------------------------
// getClientHistory
// get the clientHistory vector for the client
    vector<Transaction*> getClientHistory();

private:
    string firstName;     // first name of client
    string lastName;      // last name of client
    int accountNumber;    // account number
    Account* acctptr[10]; // an array of Account

    // vector of Transaction pointer forTransaction history
    vector<Transaction*> clientHistory; 
};
#endif