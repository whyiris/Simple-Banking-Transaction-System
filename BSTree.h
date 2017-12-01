//---------------------------------------------------------------------------
// BSTree.h
// 
// BSTree for clientData
// clientData with same accountNumber are not allowed 
// to exist in the same tree
// Assumption: if there are two clientData with the same accountNumber
// only insert the first one and delete the second one
// 


#ifndef BSTREE_H
#define BSTREE_H
#include "clientData.h"
#include <iostream>
#include <fstream>
using namespace std;

class BSTree {

public:

//---------------------------------------------------------------------------
// constructor
    BSTree();

//---------------------------------------------------------------------------
// destructor
    ~BSTree();

//---------------------------------------------------------------------------
// insert
// insert the clienrData in tree 
    bool insert(clientData* );

//---------------------------------------------------------------------------
// buildTree
    void buildTree(ifstream&);

//---------------------------------------------------------------------------
// isEmpty
// determine wheather the tree is empty
    bool isEmpty() const;

//---------------------------------------------------------------------------
// makeEmpty
// empty the binary search tree by recursion
    void makeEmpty();

//---------------------------------------------------------------------------
// display
// display the node by recursion
    void display() const;

//---------------------------------------------------------------------------
// retrieve
// get the clientData by compare clientData
    bool retrieve(const clientData&, clientData*&);

private:
    struct Node {
        clientData* data;      // pointer to actual data stored
        Node* left;            // pointer to left child Node, left subtree
        Node* right;           // pointer to right child Node, right subtree
    };

    Node* root;

//---------------------------------------------------------------------------
// makeEmptyHelper
// a helper function to empty the tree
    void makeEmptyHelper(Node*&);

//---------------------------------------------------------------------------
// displayHelper
// display the tree in in order traversal (left, self, right)
// display the node by recursion
    void displayHelper(Node*) const;
};

#endif