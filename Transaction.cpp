//---------------------------------------------------------------------------
// Transaction.cpp
// A transaction class that have 4 transactions types
// 
// Assume the 4 transaction types in command file with correct format
// D 12341 100 (two int follow char D)
// M 12341 1000 30002 (three int follow char M)
// W 55551 1500 (two int follow char W)
// H 9999 (one int follow char H)
#include "Transaction.h"
using namespace std;

//----------------------------------------------------------------------------
// Constructor
// used when call move command
// to create a Transaction object for client
Transaction::Transaction(char tran, int account1, int a, int account2) {
    transactionType = tran;
    initialAccount = account1;
    amount = a;
    receiverAccount = account2;
}

//----------------------------------------------------------------------------
// default constructor
Transaction::Transaction() {
    initialAccount = 0;
    amount = 0;
    receiverAccount = 0;
    transactionType = ' ';
}

//----------------------------------------------------------------------------
// Deconstructor
Transaction::~Transaction() {
}

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
bool Transaction::setTransaction(istream & infile) {
    // read the first char in a line, which should be the transaction type
    infile >> transactionType;

    // use switch cases to set the data for different transaction type
    switch (transactionType) {
    
    // read the next two int for transaction type D
    case 'D': {
        infile >> initialAccount >> amount;
        return true;
    }
    
    // read the next two int for transaction type W
    case 'W': {
        infile >> initialAccount >> amount;
        return true;
    }

    // read the next three int for transaction type M
    case 'M': {
        infile >> initialAccount >> amount >> receiverAccount;
        return true;
    }

    // read the next int for transaction type H
    case 'H': {
        infile >> initialAccount;
        return true;
    }
    
    // if none of the transaction type is read
    // it is an unknown type
    default:
        string line;
        // get the whole line, 
        // so we do not need deal with the garbage data input 
        getline(infile, line);

        // display error message
        cout << "Unknown trannsaction type '";
        cout << transactionType << "'requested" << endl << endl;

        // return false since the transaction data is not set successfully
        return false;
    }
}


//----------------------------------------------------------------------------
// deposit
// to perform deposit command
// return true when deposit is perform successfully
// return false when it's not success, i.e. client cannot be found
bool Transaction::deposit(Transaction* t, BSTree& tree) {
    // get the initial account number, account type
    int i = t->getInitialAccount();
    int accountType = i % 10;
    int accountNumber = i / 10;

    // get the aomunt for the transaction
    int amount = t->getAmount();

    // instantiate a fake client by using account number
    clientData client(accountNumber);
    // an access to the desired client if the client is found in tree
    clientData* clientobjref;

    // retrieve the client from tree
    // get an access to the desired client by using clientobjref
    bool success = tree.retrieve(client, clientobjref);

    // determine whether the client is found in tree
    // when the client is found
    if (success) {
        // get the final balance after adding the amount
        int finalBalance = 
            (*clientobjref->getAccount(accountType)).getBalance() + amount;

        // set the finalbalance
        (*clientobjref->getAccount(accountType)).setBalance(finalBalance);
        
        // add the transaction to the clientHistory vector
        clientobjref->setClientHistory(t);
        return true;
    }
    // when the client is not found
    else {

        // display error message
        cout << "Unknown client ID ";
        cout << accountNumber << " requested" << endl << endl;
        
        // deallocate the transaction 
        // since it is invalid and will not delete by client
        delete t;
        return false;
    }
}



//----------------------------------------------------------------------------
// withdraw
// to perform withdraw command
// return true when withdraw is perform successfully
// return false when withdraw not success
// i.e. client cannot be found or not enough money to withdraw
bool Transaction::withdraw(Transaction* t, BSTree& tree) {
    // get the initial account number, account type
    int i = t->getInitialAccount();
    int accountType = i % 10;
    int accountNumber = i / 10;

    // get the aomunt for the withdraw
    int amount = t->getAmount();

    // instantiate a fake client by using account number
    clientData client(accountNumber);
    // an access to the desired client if the client is found in tree
    clientData* clientobjref;

    // retrieve the client from tree
    // get an access to the desired client by using clientobjref
    bool success = tree.retrieve(client, clientobjref);

    // determine whether the client is found in tree
    // when the client is found
    if (success) {
        // the finalBalance after withdraw from that account
        int finalBalance = 
            (*clientobjref->getAccount(accountType)).getBalance() - amount;

        // if the account has sufficient money to withdraw
        if (finalBalance >= 0) {
            // set the new balance to the account
            (*clientobjref->getAccount(accountType)).setBalance(finalBalance);
            // add the transaction to the clientHistory vector
            clientobjref->setClientHistory(t);
            return true;
        }
        
        // the account do not has sufficient money to withdraw
        else {
            // use the negativeBalanceHelper to see 
            // if other account have sufficient amount to withdraw
            bool successwithdraw = 
                negativeBalanceHelper(t, clientobjref, finalBalance);

            // if other account have sufficient amount
            if (successwithdraw) {
                // add the transaction to the clientHistory vector
                clientobjref->setClientHistory(t);
                return true;
            }

            // invalid transaction 
            // if other account do not have sufficient amount
            else {
                // display error message
                insufficientWithdrawlErrorMessage(t, clientobjref);

                // deallocate the transaction 
                // since it is invalid and will not be deleted by client
                delete t;
                return false;
            }
        }
    }

    // when the client is not found
    else {
        // display error message
        cout << "Unknown client ID ";
        cout << accountNumber << " requested" << endl << endl;

        // deallocate the transaction 
        // since it is invalid and will not be deleted by client
        delete t;
        return false;
    }
}



//----------------------------------------------------------------------------
// move
// to perform move command
bool Transaction::move(Transaction* t, BSTree& tree) {
    // get the initial(sender) account number, account type
    // account which send monet
    int i = t->getInitialAccount();
    int initialAccountType = i % 10;
    int initialAccountNumber = i / 10;
    
    // get the aomunt needed to move
    int amount = t->getAmount();

    // get the receiver account number, account type
    // account which receive money
    int r = t->getReceiverlAccount();
    int receiverAccountType = r % 10;
    int receiverAccountNumber = r / 10;

    // FOR SENDER ACCOUNT
    // instantiate a fake client by using account number
    clientData clientInitial(initialAccountNumber);
    // an access to the desired client if the client is found in tree
    clientData* clientobjrefInitial;
    // find the sender account from tree
    bool successI = tree.retrieve(clientInitial, clientobjrefInitial);
    
    // same as FOR RECEIVER ACCOUNT
    clientData clientReceiver(receiverAccountNumber);
    clientData* clientobjrefReceiver;
    bool successR = tree.retrieve(clientReceiver, clientobjrefReceiver);
    
    // when both account are found in tree
    if (successI && successR) {

        // the finalBalance after move from that account
        int finalBalance = 
            (*clientobjrefInitial->
                getAccount(initialAccountType)).getBalance() - amount;
        
        // if the account has sufficient money
        if (finalBalance >= 0) {

            // create a Transaction object for the receiver client
            Transaction* deposit = new Transaction('D', r, finalBalance);

            // set the balance for the sender client account
            (*clientobjrefInitial->
                getAccount(initialAccountType)).setBalance(finalBalance);

            // the final balance for the receiver account
            int finalBalanceR = 
                (*clientobjrefReceiver->
                    getAccount(receiverAccountType)).getBalance() + amount;
            
            // set the balance for the receiver client account
            (*clientobjrefReceiver->
                getAccount(receiverAccountType)).setBalance(finalBalanceR);
            
            // set client history for sender and sender by using 
            // transaction move and the new created transaction object
            clientobjrefInitial->setClientHistory(t);
            clientobjrefReceiver->setClientHistory(deposit);
            return true;
        }

        // if the account has insufficient money
        else {

            // check whether other account has sufficient amount
            bool successMove = 
                negativeBalanceHelper(t, clientobjrefInitial, finalBalance);

            // when other account has sufficient amount
            // same approach when the account has sufficient amount
            if (successMove) {

                // create a Transaction object for the receiver client
                Transaction* deposit = new Transaction('D', r, finalBalance);

                // the final balance of receiver account
                int finalBalanceR = 
                    (*clientobjrefReceiver
                        ->getAccount(receiverAccountType)).getBalance() 
                    + amount;
                
                // set the balance for receiver account
                (*clientobjrefReceiver
                 ->getAccount(receiverAccountType)).setBalance(finalBalanceR);
                
                // set client history for sender and sender by using 
                // transaction move and the new created transaction object
                clientobjrefInitial->setClientHistory(t);
                clientobjrefReceiver->setClientHistory(deposit);
                return true;
            }
            // when other account has not sufficient amount
            else {

                // display error message
                insufficientMoveErrorMessage(t, clientobjrefInitial);

                // deallocate the transaction 
                // since it is invalid and will not be deleted by client
                delete t;
                return false;
            }
        }
    }
    // when either client is not found
    else {
        // display error message
        cout << "Unknown client ID ";
        cout << initialAccountNumber << " or " << receiverAccountNumber;
        cout << " requested" << endl << endl;

        // deallocate the transaction 
        // since it is invalid and will not be deleted by client
        delete t;
        return false;
    }
}


//----------------------------------------------------------------------------
// negativeBalanceHelper
// for withdraw and move
// when the sender account does not have sufficient amount
// to check the other account
// only work for money market and bond accounts
// return true when the amount successfully cover by the other account
// false when the amount cannot be coverd by the other account
bool Transaction::negativeBalanceHelper
(Transaction* t, clientData*& c, int balance) {
    // get the accountType
    int i = t->getInitialAccount()%10;
    switch (i) {
    
    // for Money Market
    case 0:
    {    
        // the account balance after it is cover
        int b = (*c->getAccount(1)).getBalance() + balance;
        // there is enough amount to cover
        if (b >= 0) {
            // set the account balance after move or withdraw
            (*c->getAccount(0)).setBalance(0);
            (*c->getAccount(1)).setBalance(b);
            return true;
        }
        // the Prime Money Market does not have enough amount to cover
        else {
            return false;
        }
    }
    // for prime money market
    // same approach
    case 1:
    {
        int b = (*c->getAccount(0)).getBalance() + balance;
        if (b >= 0) {
            (*c->getAccount(1)).setBalance(0);
            (*c->getAccount(0)).setBalance(b);
            return true;
        }
        // the Money Market does not have enough amount to cover
        else {
            return false;
        }
    }
    // for Long-Term Bond
    case 2:
    {
        int b = (*c->getAccount(3)).getBalance() + balance;
        if (b >= 0) {
            (*c->getAccount(2)).setBalance(0);
            (*c->getAccount(3)).setBalance(b);
            return true;
        }
        else {
            return false;
        }
    }
    // for Short-Term Bond
    case 3:
    {
        int b = (*c->getAccount(2)).getBalance() + balance;
        if (b >= 0) {
            (*c->getAccount(3)).setBalance(0);
            (*c->getAccount(2)).setBalance(b);
            return true;
        }
        else {
            return false;
        }
        break;
    }
    // for other account
    // which do not follow the rule
    default:
        return false;
    }

}

//----------------------------------------------------------------------------   
// insufficientWithdrawlErrorMessage
// when the withdraw transaction is not success 
// (not sufficient funds to withdraw)
// display the error message
void Transaction::insufficientWithdrawlErrorMessage
(Transaction* t, clientData* c) const {
    // get the account number, account type
    int i = t->getInitialAccount();
    int accountType = i % 10;

    string accountT = (*c->getAccount(accountType)).getType();

    // display error message
    cout << "Withdrawal not performed on " << accountT << " for client ";
    cout << c->getAccountNumber() << ";" << endl;
    cout << "     insufficient funds" << endl<<endl;
}


//----------------------------------------------------------------------------   
// insufficientMoveErrorMessage
// when the move transaction is not success 
// (not sufficient funds to move)
// display the error message
void Transaction::insufficientMoveErrorMessage
(Transaction* t, clientData* c) const {
    // get the account number, account type
    int i = t->getInitialAccount();
    int accountType = i % 10;
    string accountT = (*c->getAccount(accountType)).getType();

    // display error message
    cout << "Move not performed on " << accountT << " for client ";
    cout << c->getAccountNumber() << ";" << endl;
    cout << "     insufficient funds" << endl<<endl;
}

//----------------------------------------------------------------------------
// getTransactionType
// get the Transaction Type: 
// D (Deposit) / W (Withdraw) / M (Move) / H (History)
char Transaction::getTransactionType() const {
    return transactionType;
}

//----------------------------------------------------------------------------
// getAmount
// get the amount for transaction
// can be zero when it is H
int Transaction::getAmount() const {
    return amount;
}

//----------------------------------------------------------------------------
// getInitialAccount
// get the initial account for transaction
// only return valid account when the transaction type is D, W, M
int Transaction::getInitialAccount() const {
    return initialAccount;
}

//----------------------------------------------------------------------------
// getReceiverAccount
// get the receiver account for transaction
// only return valid account when the transaction type is M
int Transaction::getReceiverlAccount() const {
    return receiverAccount;
}

//----------------------------------------------------------------------------
// showHistory
// show the transaction history of required client
void Transaction::showHistory(Transaction * t, BSTree & tree) {
    // get the client account number
    int i = t->getInitialAccount();
    
    // instantiate a fake client by using account number
    clientData client(i);
    // an access to the desired client if the client is found in tree
    clientData* clientobjref;

    // retrieve the client from tree
    bool success = tree.retrieve(client, clientobjref);

    // when it is successfully retrieve from the tree
    // valid client
    if (success) {
        
        // display the history with certain format
        cout << "History of transactions for client ";
        cout << clientobjref->getFirstName() << " ";
        cout << clientobjref->getLastName();
        cout << ", client ID = " << clientobjref->getAccountNumber()<< endl;
        cout << "Type      Amount  Detail" << endl;
        cout << "--------- ------- --------------------------------------";
        cout << endl;
        
        // get the clientHistory vector from client object
        vector<Transaction*> clientHistory 
             = clientobjref->getClientHistory();
        
        // use iterator to display the transaction
        for (std::vector<Transaction*>::iterator it 
             = clientHistory.begin(); it != clientHistory.end(); ++it)
            // get the transaction object
            std::cout << **it << endl;
    }
    // when the client is not found in tree
    // invalid client
    else {
        // display error message
        cout << "Unknown client ID " << i << " requested" << endl;
    }
    cout << endl;

    // delete the transaction object
    delete t;
}

//----------------------------------------------------------------------------   
// operator<<
// overload operator<< to display Transaction object
ostream & operator<<(ostream & output, const Transaction& t) {
    // type of Transaction object
    char type = t.getTransactionType();
    int i = t.getInitialAccount() % 10;

    // create a fake Account object to get the account name
    Account a(i);
    
    // display the Transaction depends on transaction type
    // do not required for H(showHistory) 
    switch (type) {
    case 'D': {
        output << "deposit   $" << setw(6) << t.getAmount() << " into ";
        output << a.getType() << " fund";
        return output; 
    }
    case 'W': {
        output << "withdraw  $" << setw(6) << t.getAmount() << " from ";
        output << a.getType() << " fund";
        return output;
    }
    case 'M': {
        int rType = t.getReceiverlAccount() % 10;
        Account r(rType);
        output << "move      $" << setw(6) << t.getAmount() << " from ";
        output << a.getType() << " fund" <<endl;
        output << "                  ";
        output << "to " << r.getType() << " fund for client ";
        output << t.getReceiverlAccount() / 10;
        return output;
    }
    }
    // for invalid transaction command
    return output;
}





