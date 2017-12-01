//---------------------------------------------------------------------------
// Account.h
// 
// one of the ten accounts of client
// it has initial balance and balance (intermediate/final balance)
// it has integer to represent the account type
// it has a string to represent the account type of account

#ifndef Account_H
#define Account_H
#include <iomanip>
#include <vector>
#include<iostream>
using namespace std;

class Account {

//---------------------------------------------------------------------------
// operator<<
// Overloaded output operator for class clientData
// display the initial balance of account
    friend ostream& operator<<(ostream &, const Account &);

public:
//---------------------------------------------------------------------------
// constructor
// instantiate the Account class with two parameter
// 1st parameter: the accountType
// 2nd parameter: the beginningBalance of that account, which initialize to 0
    Account(int accountType, int = 0);
    
//---------------------------------------------------------------------------
// destructor
    ~Account();

//----------------------------------------------------------------------------
// getInitialBalance
// get the initial balance of account
    int getInitialBalance() const;

//----------------------------------------------------------------------------
// getBalance
// get the intermediate or final balance of account
    int getBalance() const;

//----------------------------------------------------------------------------
// setBalance
// set the balance of account
    void setBalance(int);

//----------------------------------------------------------------------------
// getType
// get the accountType
    string getType() const;

//----------------------------------------------------------------------------
// displayFinalBalance
// show the balance of account
    void displayFinalBalance();

private:
    int initialBalance;    // the initial balance
    int balance;           // the intermediate or final balance
    int accountType;       // the integer to represent the account type
    string type;           // the account type of account
};

#endif