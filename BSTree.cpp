//---------------------------------------------------------------------------
// BSTree.cpp
// 
// BSTree for clientData
// clientData with same accountNumber are not allowed 
// to exist in the same tree
// Assumption: if there are two clientData with the same accountNumber
// only insert the first one and delete the second one
// 


#include "BSTree.h"
#include "clientData.h"
#include <iostream>
#include <fstream>

using namespace std;

//---------------------------------------------------------------------------
// constructor
BSTree::BSTree() {
    root = NULL;
}

//---------------------------------------------------------------------------
// destructor
BSTree::~BSTree() {
    makeEmpty();
}

//---------------------------------------------------------------------------
// insert
// insert the clienrData in tree
bool BSTree::insert(clientData* dataptr) {
    // create a new node
    Node* ptr = new Node;
    if (ptr == NULL) return false;            // out of memory
    // set the data, left and right pointer of the node
    ptr->data = dataptr;
    ptr->left = ptr->right = NULL;
    
    // when the tree is empty, insert to the root
    if (isEmpty()) {
        root = ptr;
    }

    // when the tree is not empty
    else {
        Node* current = root;                 // walking pointer
        bool inserted = false;                // whether inserted yet

        // if item is less than current item, insert in left subtree,
        // otherwise insert in right subtree
        while (!inserted) {
            if (*ptr->data < *current->data) {
                if (current->left == NULL) {          // insert left
                    current->left = ptr;
                    inserted = true;
                }
                else
                    current = current->left;          // one step left
            }
            else if (*ptr->data > *current->data) {
                
                if (current->right == NULL) {         // insert right
                    current->right = ptr;
                    inserted = true;
                }
                else
                    current = current->right;          // one step right
            }
            else {
                // when the client already exist in the tree
                delete ptr;                           
            }
        }
    }
    return true;
}

//---------------------------------------------------------------------------
// buildTree
void BSTree::buildTree(ifstream& infile) {
    clientData* ptr;
    bool successfulRead;                         // read good data
    bool success;                                // successfully insert
    for (;;) {
        ptr = new clientData;
        successfulRead = ptr->setData(infile);   // fill the NodeData object
        if (infile.eof()) {
            delete ptr;
            break;
        }

        // insert good data into the list, otherwise ignore it
        if (successfulRead) {
            success = insert(ptr);
            // cout << "success"<< endl;
        }
        else {
            delete ptr;
        }
        if (!success) {
            delete ptr;
        }
        
    }
}

//---------------------------------------------------------------------------
// isEmpty
// determine wheather the tree is empty
bool BSTree::isEmpty() const {
    return root == NULL;
}

//---------------------------------------------------------------------------
// makeEmpty
// empty the binary search tree by recursion
void BSTree::makeEmpty() {
    makeEmptyHelper(root);
}

//---------------------------------------------------------------------------
// makeEmptyHelper
// a helper function to empty the tree
void BSTree::makeEmptyHelper(Node*& t) {
    if (t != NULL) {
        
        // empty the left node
        makeEmptyHelper(t->left);
        
        // empty the right node
        makeEmptyHelper(t->right);

        // empty the current node
        delete t->data;
        delete t;
    }
    t = NULL;
}

//---------------------------------------------------------------------------
// display
// display the node by recursion
void BSTree::display() const {
    displayHelper(root);
}

//---------------------------------------------------------------------------
// displayHelper
// display the tree in in order traversal (left, self, right)
// display the node by recursion
void BSTree::displayHelper(Node * n) const {
    if (n != NULL) {
        // left node
        displayHelper(n->left);
        // current
        cout << *n->data<< endl;
        // right node
        displayHelper(n->right);
    }
}

//---------------------------------------------------------------------------
// retrieve
// get the clientData by compare clientData
bool BSTree::retrieve(const clientData& c, clientData *& objref) {
    // cout << "in retrieve function:  " << c << endl;
    Node* current = root;
    // cout << "in retrieve function2:  " << *current->data << endl;
    if (root == NULL) {
        //cout << "NOT found" << endl;
        return false;
    }

    while (current != NULL) {
        if (c == *current->data) {
            objref = current->data;
            //cout << "found:  " << c << endl;
            return true;
        }
        else if (c > *current->data) {
            
            if (current->right == NULL) {
                //cout << "NOT found" << endl;
                return false;
            } 
            else {
                current = current->right;
                //cout << "TOO LARGE:  " << *current->data << endl;

            }
        }
        else if(c < *current->data) {
            //current = current->left;
            if (current->left == NULL) {
                //cout << "NOT found" << endl;
                return false;
            }
            else {
                current = current->left;
                //cout << "TOO SMALL:  " << *current->data << endl;
            }
        }
    }

    return false;
}


