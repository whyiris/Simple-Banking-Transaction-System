//---------------------------------------------------------------------------
// Manager.cpp
// 
// to build a binary search tree for client
// build a queue for valid command (D/W/M/H)
// then processTransactions, that is perform command
// and printReport for all clients in binary search tree
//
// Assume the tree and commandQueue are build successfully
// so it can run business

#include "Manager.h"

using namespace std;

//----------------------------------------------------------------------------
// default constructor
Manager::Manager() {
}

//----------------------------------------------------------------------------
// Destructor
Manager::~Manager() {
}

//----------------------------------------------------------------------------
// build
// basically build a binary search tree for client
// and build a queue for valid command (D/W/M/H)
void Manager::build() {
    // the client data file
    ifstream infile("lab5data.txt");
    // check for existence of file
    if (!infile) {
        cout << "File could not be opened." << endl;
    }
    // build the BSTree for client
    buildTree(infile);
    infile.close();

    // the command data file
    ifstream infile2("lab5command.txt");
    // check for existence of file
    if (!infile2) {
        cout << "File could not be opened." << endl;
    }
    // build the queue for valid command (D/W/M/H)
    buildQueue(infile2);
    infile2.close();
}

//----------------------------------------------------------------------------
// buildTree
// build a binary search tree for client
void Manager::buildTree(ifstream& infile) {
    tree.buildTree(infile);
}

//----------------------------------------------------------------------------
// buildQueue
// build a queue for valid command(D / W / M / H)
void Manager::buildQueue(ifstream & infile) {
    // create a transaction pointer
    Transaction* ptr;

    bool success; // set the command successfully or not
    for (;;) {
        ptr = new Transaction;

        // when the file is end
        if (infile.eof()) {
            delete ptr;
            break;
        }

        // set Transaction command
        success = ptr->setTransaction(infile);
        if (success) {
            // enqueue the commandQueue
            commandQueue.push(ptr);
        }
        else {
            // delete the Transaction when it is not successfully set
            delete ptr;
        }
    }
}

//----------------------------------------------------------------------------
// processTransactions
// 
void Manager::processTransactions() {
    // Transaction type
    char type;

    // dequeue from commandQueue
    while (!commandQueue.empty()) {

        // get the Transaction
        Transaction* t = commandQueue.front();
        
        // remove the Transaction from queue
        commandQueue.pop();
        // get the transaction type 
        type = t->getTransactionType();

        // to determine which transaction should be perform
        switch (type) {
        case 'D': 
            t->deposit(t, tree); 
            break;
        case 'W':
            t->withdraw(t, tree);
            break;
        case 'M': 
            t->move(t, tree);
            break;
        case 'H':
            t->showHistory(t, tree);
            break;
        }
    }
}

//----------------------------------------------------------------------------
// runBusiness
// process Transaction and print the report for client
void Manager::runBusiness() {
    processTransactions();
    printReport();

}

//----------------------------------------------------------------------------
// printReport
// print the binary search tree in in orde traversal
// when printing, include the account number, first name, last name, 
// initial and final balance for the ten accounts
// Example format
// 1111  sammy spider
// Initial Balances : 4000   500    0    0    0    0    0    0    0    0
// Final Balances :   4000   500    0    0    0    0    0    0    0    0
void Manager::printReport() {
    tree.display();
}
