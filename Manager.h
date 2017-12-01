//---------------------------------------------------------------------------
// Manager.h
// 
// to build a binary search tree for client
// build a queue for valid command (D/W/M/H)
// then processTransactions, that is perform command
// and printReport for all clients in binary search tree
// 
// Assume the tree and commandQueue are build successfully
// so it can run business

#ifndef MANAGER_H
#define MANAGER_H
#include "clientData.h"
#include "Account.h"
#include "BSTree.h"
#include "Transaction.h"
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

class Manager {

public:
//----------------------------------------------------------------------------
// default constructor
    Manager();

//----------------------------------------------------------------------------
// Destructor
    ~Manager();

//----------------------------------------------------------------------------
// build
// basically build a binary search tree for client
// and build a queue for valid command (D/W/M/H)
    void build();

//----------------------------------------------------------------------------
// buildTree
// build a binary search tree for client
    void buildTree(ifstream&);

//----------------------------------------------------------------------------
// buildQueue
// build a queue for valid command(D / W / M / H)
    void buildQueue(ifstream&);

//----------------------------------------------------------------------------
// processTransactions
// 
    void processTransactions();

//----------------------------------------------------------------------------
// runBusiness
// process Transaction and print the report for client
    void runBusiness();

//----------------------------------------------------------------------------
// printReport
// print the binary search tree in in orde traversal
// when printing, include the account number, first name, last name, 
// initial and final balance for the ten accounts
// Example format
// 1111  sammy spider
// Initial Balances : 4000   500    0    0    0    0    0    0    0    0
// Final Balances :   4000   500    0    0    0    0    0    0    0    0

    void printReport();

private:

    BSTree tree;
    queue<Transaction*> commandQueue;
};

#endif