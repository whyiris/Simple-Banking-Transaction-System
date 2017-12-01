//---------------------------------------------------------------------------
// Transaction.h
// A transaction class that have 4 transactions types
// 
// Assume the 4 transaction types in command file with correct format
// D 12341 100 (two int follow char D)
// M 12341 1000 30002 (three int follow char M)
// W 55551 1500 (two int follow char W)
// H 9999 (one int follow char H)

#ifndef Transaction_H
#define Transaction_H

#include"BSTree.h"
#include <string>
#include <queue>
#include <iostream>
using namespace std;
//using namespace boost;

class Transaction {
    friend ostream& operator<<(ostream &, const Transaction &);
public:
//----------------------------------------------------------------------------
// Constructor
// used when call move command
// to create a Transaction object for client
    Transaction(char, int, int = -1, int = -1);

//----------------------------------------------------------------------------
// default constructor
    Transaction();

//----------------------------------------------------------------------------
// Deconstructor
    ~Transaction();

//----------------------------------------------------------------------------
// setTransaction
// set the transaction object when read the command data file
// Format is like this:
// D 12341 100 (two int follow char D)
// M 12341 1000 30002 (three int follow char M)
// W 55551 1500 (two int follow char W)
// H 9999 (one int follow char H)
// for other char, will deem as unknown transaction type
// assume all the define transaction type (D, M, W, H) in correct format
    bool setTransaction(istream&);

//----------------------------------------------------------------------------
// deposit
// deposit funds in the account
    bool deposit(Transaction*, BSTree&);

//----------------------------------------------------------------------------
// withdraw
// withdraw funds
// if withdraw from a money market account with insufficient funds, 
// but if it can be covered with funds from another money market, 
// the desired amount (only the partial amount needed to cover the withdrawal)
// is moved to theat money market account
// Bond accounts are handled similarly
    bool withdraw(Transaction*, BSTree&);

//----------------------------------------------------------------------------
// move
// move funds
// if move from a money market account with insufficient funds, 
// but if it can be covered with funds from another money market, 
// the desired amount (only the partial amount needed to cover the withdrawal)
// is moved to theat money market account
// Bond accounts are handled similarly
    bool move(Transaction*, BSTree&);

//----------------------------------------------------------------------------
// showHistory
    void showHistory(Transaction*, BSTree&);

//----------------------------------------------------------------------------
// getTransactionType
// get the Transaction Type: 
// D (Deposit) / W (Withdraw) / M (Move) / H (History)
    char getTransactionType() const;

//----------------------------------------------------------------------------
// getAmount
// get the amount for transaction
// can be zero when it is H
    int getAmount() const;

//----------------------------------------------------------------------------
// getInitialAccount
// get the initial account for transaction
// only return valid account when the transaction type is D, W, M
    int getInitialAccount() const;

//----------------------------------------------------------------------------
// getReceiverAccount
// get the receiver account for transaction
// only return valid account when the transaction type is M
    int getReceiverlAccount() const;

private:

    char transactionType;   // the transaction Type (D / W / M / H)
    int initialAccount;     // the desired account
    int amount;             // the amount that need to deposit/withdraw
    int receiverAccount;    // the receiver account for move transaction

//----------------------------------------------------------------------------
// negativeBalanceHelper
// for withdraw and move
// when the sender account does not have sufficient amount
// to check the other account
// only work for money market and bond accounts
// return true when the amount successfully cover by the other account
// false when the amount cannot be coverd by the other account
    bool negativeBalanceHelper(Transaction * t, clientData *& c, int balance);

//----------------------------------------------------------------------------   
// insufficientWithdrawlErrorMessage
// when the withdraw transaction is not success 
// (not sufficient funds to withdraw)
// display the error message
    void insufficientWithdrawlErrorMessage(Transaction*, clientData *) const;

//----------------------------------------------------------------------------   
// insufficientMoveErrorMessage
// when the move transaction is not success 
// (not sufficient funds to move)
// display the error message
    void insufficientMoveErrorMessage(Transaction*, clientData *) const;

};

#endif