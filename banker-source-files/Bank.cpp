#include "Bank.h"

Bank::Bank()
{
	//Default 
}

Bank::Bank(string name)
{
	bank_name_ = name;
}

Bank::~Bank()
{
	//Default
}

bool Bank::Execute(string fileName)
{
	if(ProcessFile(fileName))
	{
		ProcessQueue();
		Display();
		return true;
	}
	else
	{
		cout << "\nERROR: UNABLE TO PROCESS FILE" << endl;
	}
	return false;
}

string Bank::GetBankName()
{
	return bank_name_;
}

bool Bank::ProcessFile(string fileName)
{
    ifstream fileObject;
	fileObject.open(fileName);

	if (fileObject.is_open())
	{		
		string str;
		while (getline(fileObject, str))
		{
			transaction_queue_.push(Transaction(str));
		}
	}
	else
	{
		cout << "\nERROR: FILE " << fileName << " NOT FOUND" << endl;
		return false;
	}
	
	fileObject.close();
	return true;
}

void Bank::ProcessQueue()
{
	while(!(transaction_queue_.empty()))
	{
		ProcessTransaction(transaction_queue_.front());
		transaction_queue_.pop();
	}
}

void Bank::ProcessTransaction(Transaction &tr)
{			
	//If the action is connecting to/opening an Account
	if(tr.GetType() == "O")
	{	
		if(ptr != nullptr)
		{
			if(ptr->GetID() == tr.GetAccountID())
			{
				cout << "\nERROR: ACCOUNT " << tr.GetAccountID() 
				<< " IS ALREADY OPEN. TRANSACTION REFUSED." << endl;
				return;
			}
		}
		//Connecting to the Account
		//Helper function OpenAccount will take care of connecting to an Account
		if(tr.GetFirstName() != "" && tr.GetLastName() != "")
		{
			ptr = nullptr;
			ptr = ConnectAccount(tr.GetAccountID(), tr.GetFirstName(), tr.GetLastName());
			return;
		}
		else
		{
			cout << "\nERROR: MISSING ACCOUNT HOLDER NAME" << endl;
			return;
		}
	}

	if(ptr != nullptr)
	{
		if(ptr->GetID() != tr.GetAccountID())
		{
			cout << "\nERROR: " << tr.GetDetails()
			<< " ACCOUNT ID " << tr.GetAccountID() 
			<< " NEEDS TO BE OPENED FIRST" 
			<< " BEFORE ANY FURTHER PROCESSING." << endl;
			cout << "CURRENT OPENED ACCOUNT ID: " << ptr->GetID() << endl;
			return;
		}
	}

	if(ptr != nullptr){
		//Other actions
		if(tr.GetType() == "D")
		{
			if(accounts_list_.Find(tr.GetAccountID()))
			{
				ptr->Deposit(tr.GetAmount(), tr.GetFundID(), tr.GetDetails());
			}
			else
			{
				cout << "\nERROR: " << tr.GetDetails()
				<< "---ACCOUNT WITH ID " << tr.GetAccountID()
				<< " DOES NOT EXIST." << endl;
			}
		}

		else if(tr.GetType() == "W")
		{
			if(accounts_list_.Find(tr.GetAccountID()))
			{
				ptr->WithDraw(tr.GetAmount(), tr.GetFundID(), tr.GetDetails());
			}
			else
			{
				cout << "\nERROR: " << tr.GetDetails()
				<< "---ACCOUNT WITH ID " << tr.GetAccountID()
				<< " DOES NOT EXIST." << endl;
			}
		}
		
		else if(tr.GetType() == "T")
		{
			if(accounts_list_.Find(tr.GetAccountID()))
			{
				if(accounts_list_.Find(tr.GetOtherAccountID()))
				{
					ptr->Transfer(tr.GetAmount(), tr.GetFundID(), 
					*ConnectAccount(tr.GetOtherAccountID(),tr.GetFirstName(), tr.GetLastName()), 
					tr.GetOtherFundID(), tr.GetDetails());
				}
				else
				{
					cout << "\nERROR: " << tr.GetDetails()
					<< "---ACCOUNT WITH ID " << tr.GetOtherAccountID()
					<< " DOES NOT EXIST." << endl;
				}
			}
			else
			{
				cout << "\nERROR: " << tr.GetDetails()
				<< "---ACCOUNT WITH ID " << tr.GetAccountID()
				<< " DOES NOT EXIST." << endl;
			}
		}

		else if(tr.GetType() == "H")
		{
			//Getting specific Fund history
			if(tr.GetFundID() >= 0)
			{
				ptr->FundHistory(tr.GetFundID());
			}
			
			//Getting Account history
			else
			{
				ptr->History(tr.GetDetails());
			}
		}
		//Actions that are not in accordance with any of the processes
		else
		{
			cout << "ERROR: ERRONEROUS ACTIONS" << endl;
		}
	}

	else
	{
		cout << "ERROR: NO TRANSACTIONS WERE FOUND" << endl;
	}
	
	ptr->RecordHistory(tr.GetDetails());
	return;
}

Account* Bank::ConnectAccount(int id, string first="", string last="")
{
	//If BinaryTree look up Account using id does not find an Account
	//Create a new Account
	if(!(accounts_list_.Find(id)))
	{
		accounts_list_.OpenAccount(id, first, last);
	}
	//Connect to the Account in the Tree
	return accounts_list_.Retrieve(id);
}

void Bank::Display()
{
	cout << "\nPROCESSING DONE. FINAL BALANCES:" << endl;
	accounts_list_.Display();	
}