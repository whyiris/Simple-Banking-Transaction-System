//---------------------------------------------------------------------------
// main.cpp

#include"Manager.h"
#include<iostream>
#include<fstream>
#include<queue>

using namespace std;

int main() {

    // instantiate a firm
    Manager firm;
    
    // build binary search tree for client and build commandQueue for command
    firm.build();

    // process the transaction and 
    // print the report for all clients in binary search tree 
    // in in order tranversal
    firm.runBusiness();


}