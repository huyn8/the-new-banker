#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <queue>
#include <string>
#include <vector>
#include "Fund.h"

using namespace std;

/*
* This class represents an in which the Bank will use
* to create an Account for the client/user of the Bank
* Each Account will have a default of ten Funds
*/
class Account
{
    friend ostream &operator<<(ostream &outStream, const Account& account)  
    { 
       outStream << "\n-------------- ACCOUNT SUMMARY ---------------"
       << "\nAccount: " << account.GetFirstName() << " " << account.GetLastName()
       << "---ID: " << account.GetID() 
       << "\nTotal Balance: $" << account.GetBalance() << "\n" << "\nIndividual Fund Balance:\n";

       for(int i = 0; i < 10; i++)
       {
           outStream << account.GetFundName(i) << ": $" << account.GetFundBalance(i) << "\n";
       }
       outStream << "----------- END OF ACCOUNT SUMMARY -----------" << endl;
       return outStream;
    }

public:
    //CONSTRUCTORS-DESTRUCTOR
    Account();
    Account(int id);
    Account(int id, string first, string last);
    ~Account();

    /*
    * Most of these functions are self-explanatory
    * These are functions in which an Account will use 
    * to change the state/data associated with an Account
    * 
    * Note:
    * History() is used for an Account history
    * FundHistory() is used for a specific Fund history
    */
    bool Deposit(int amount, int fundID, string transactionHistory);
    bool WithDraw(int amount, int fundID, string transactionHistory);
    bool Transfer(int amount, int fromFundID, Account &toAccount, int toFundID, string transactionHistory);
    void History(string transactionHistory);
    void FundHistory(int fundID);
    void RecordHistory(string transactionHistory);
    void RecordFundHistory(string transactionHistory, int fundID);

    //GETTERS
    int GetBalance() const;
    int GetFundBalance(int fundID) const;
    string GetFundName(int fundID) const;
    string GetFirstName() const;
    string GetLastName() const;
    int GetID() const;

private:
	//INTERNAL DATA MEMBERS
    void CreateFunds();

    string first_name_, last_name_;
    int id_;

    queue <string> transaction_history_;
    vector <Fund> funds_;
};

#endif 