//---------------------------------------------------------------------------
// Account.cpp
// 
// one of the ten accounts of client
// it has initial balance and balance (intermediate/final balance)
// it has integer to represent the account type
// it has a string to represent the account type of account

#include "Account.h"

//---------------------------------------------------------------------------
// constructor
// instantiate the Account class with two parameter
// 1st parameter: the accountType
// 2nd parameter: the beginningBalance of that account, which initialize to 0
Account::Account(int t, int beginBalance) {
    accountType = t;

    // set the initialBalance
    initialBalance = beginBalance;
    balance = beginBalance;

    // set the type depends of the integer 
    // to represent the account type(accountType)
    switch (accountType) {
    case 0: type = "Money Market";
        break;
    case 1: type = "Prime Money Market";
        break;
    case 2: type = "Long-Term Bond";
        break;
    case 3: type = "Short-Term Bond";
        break;
    case 4: type = "500 Index Fund";
        break; 
    case 5: type = "Capital Value Fund";
        break;
    case 6: type = "Growth Equity Fund";
        break;
    case 7: type = "Growth Index Fund";
        break;
    case 8: type = "Value Fund";
        break;
    case 9: type = "Value Stock Index";
        break;
    }
}

//---------------------------------------------------------------------------
// destructor
Account::~Account() {
}

//----------------------------------------------------------------------------
// getInitialBalance
// get the initial balance of account
int Account::getInitialBalance() const {
    return initialBalance;
}

//----------------------------------------------------------------------------
// getBalance
// get the intermediate or final balance of account
int Account::getBalance() const {
    return balance;
}

//----------------------------------------------------------------------------
// setBalance
// set the balance of account
void Account::setBalance(int b) {
    balance = b;
}

//----------------------------------------------------------------------------
// getType
// get the accountType
string Account::getType() const {
    return type;
 }

//----------------------------------------------------------------------------
// displayFinalBalance
// show the balance of account
void Account::displayFinalBalance() {
    cout << setw(6) << getBalance();
}

//---------------------------------------------------------------------------
// operator<<
// Overloaded output operator for class clientData
// display the initial balance of account
ostream & operator<<(ostream & output, const Account & acct) {
    output << setw(6) << acct.getInitialBalance();
    return output;
}