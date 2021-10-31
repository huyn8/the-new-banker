#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Account.h"

/*
* This class represents a BinarySearchTree in which the Bank will use
* to store all of its Accounts
* The Accounts in the BinarySearchTree will be accessible for later
* processing by using the utility functions below 
*/
class BinaryTree
{
public:
    //CONSTRUCTORS-DESTRUCTOR
    BinaryTree();
    ~BinaryTree();

    //UTILITY FUNCTIONS
    bool isEmpty();
    bool Find(int accountID);
    bool OpenAccount(int accountID, string first, string last);
    void Display();
    Account* Retrieve(int accountID);

private:
	//INTERNAL DATA MEMBERS
    struct Node
    {
        int accountID_;
        Account* data;
        Node* right_;
        Node* left_;
    };
    Node* root_;

	//INTERNAL HELPER FUNCTIONS
    bool FindHelper(int accountID, Node*& subRoot);
    bool OpenAccountHelper(int accountID, string first, string last, Node*& subRoot);   
    Account* RetrieveHelper(int accountID, Node*&  subRoot);
    void DisplayHelper(Node*&  subRoot);
    void Flush(Node*&  subRoot);
};

#endif 