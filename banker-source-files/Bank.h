#ifndef BANK_H
#define BANK_H

#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include "BinaryTree.h"
#include "Account.h"
#include "Transaction.h"

using namespace std;

/*
* This class represents a Bank in which the user will 
* interact with by passing in a text file with all 
* appropriate transactions and the Bank will process
* those transactions according to the order in which 
* the transactions are input
*/
class Bank
{
    public:
	//CONSTRUCTORS-DESTRUCTOR
    Bank();
	Bank(string name);
    ~Bank();

	//CLIENT-SIDE FUNCTIONS
	
	/*
	* The user/client will be able to use Execute() to
	* start the program 
	* GetBankName() will return the name of the Bank if
	* a name was given at the time a Bank is constructed
	*/
	bool Execute(string fileName);
	string GetBankName();

    private:
	//INTERNAL FUNCTION

	/*
	* The below internal functions are in charge of processing an input
	* and producing an output when the program is run
	*
	* ProcessFile() is used to process input file and enqueue Transactions
	* into an internal Queue for later processing
	*
	* ProcessQueue() is used after the Queue has been initilized with
	* Transactions from the previous step
	*
	* Display() is used to display all Accounts in the Bank after
	* the Queue has been successfully and completely processed
	*/
	bool ProcessFile(string fileName);
	void ProcessQueue();
	void Display();

	//INTERNAL HELPER FUNCTIONS
	
	/*
	* ProcessTransaction() is used by ProcessQueue() as a helper function
	* to help process every Transaction in the Queue
	*
	* ConnectAccount() is used by ProcessTransaction() as a helper function
	* to help connect to an Account or create a new Account if one does not
	* already exist in the internal BinarySearchTree
	* All Accounts are store approriately in the BinarySearchTree
	* No duplicated Accounts are allowed
	*/
    void ProcessTransaction(Transaction &transaction);
	Account* ConnectAccount(int id, string first, string last);

	//INTERNAL DATA MEMBERS
	string bank_name_;
	Account* ptr = nullptr;
    BinaryTree accounts_list_;
    queue<Transaction> transaction_queue_;
};



#endif 