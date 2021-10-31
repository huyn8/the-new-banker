#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
    root_ = nullptr;
}

BinaryTree::~BinaryTree()
{
    Flush(root_);
    root_ = nullptr;
}


bool BinaryTree::isEmpty() 
{
    if(root_ == nullptr)
    {
        return true;
    }
    return false;
}

bool BinaryTree::Find(int accountID)
{
   return FindHelper(accountID, root_);
}

bool BinaryTree::FindHelper(int accountID, Node*& subRoot)
{
    if(subRoot != nullptr)
    {
        if(accountID == subRoot->accountID_)
        {
            return true;
        }

        else if(accountID > subRoot->accountID_)
        {
            return FindHelper(accountID, subRoot->right_);
        }

        else if(accountID < subRoot->accountID_)
        {
            return FindHelper(accountID, subRoot->left_);
        }
    }
    return false;
}

Account* BinaryTree::Retrieve(int accountID)
{
    return RetrieveHelper(accountID, root_);
}

//This function is a little bit sus
Account* BinaryTree::RetrieveHelper(int accountID, Node*& subRoot)
{
    if(subRoot != nullptr)
    {
        if(accountID == subRoot->accountID_)
        {
            return subRoot->data;
        }

        else if(accountID > subRoot->accountID_)
        {
            return RetrieveHelper(accountID, subRoot->right_);
        }

        else if(accountID < subRoot->accountID_)
        {
            return RetrieveHelper(accountID, subRoot->left_);
        }
    }
    return root_->data;
}

bool BinaryTree::OpenAccount(int accountID, string first, string last)
{
    return OpenAccountHelper(accountID, first, last, root_);
}

bool BinaryTree::OpenAccountHelper(int accountID, string first, string last, Node*& subRoot)
{
    //no duplicated Accounts allowed
    if(subRoot != nullptr)
    {
        if(accountID == subRoot->accountID_)
        {
            return false;
        }
    }

    //Adding to the root
    if(subRoot == nullptr)
    {
        Node* newNode = new Node;
        newNode->data = new Account(accountID, first, last);
        newNode->accountID_ = accountID;
        newNode->left_ = nullptr;
        newNode->right_ = nullptr;

        if(root_ == nullptr)
        {
            root_ = newNode;//when tree is empty
        }
       
        else 
        {
            subRoot = newNode;//when tree is not empty
        }
        return true;
    }

    //If the accountID is smaller
    if(accountID < subRoot->accountID_)
    {
        return OpenAccountHelper(accountID, first, last, subRoot->left_);
    }

    //If the accountID is bigger
    else if(accountID > subRoot->accountID_)
    {
        return OpenAccountHelper(accountID, first, last, subRoot->right_);
    }
    else
    return false;
}

void BinaryTree::Flush(Node*& subRoot)
{
    if(subRoot == nullptr)
    {
        return;
    }
    Flush(subRoot->left_);
    Flush(subRoot->right_);
    delete subRoot->data;
    delete subRoot;
}

void BinaryTree::Display()
{
    DisplayHelper(root_);
}

void BinaryTree::DisplayHelper(Node*& subRoot)
{
    if(subRoot == nullptr)
    {
        return;
    }

    cout << *subRoot->data << endl;
    DisplayHelper(subRoot->left_);
    DisplayHelper(subRoot->right_);
}