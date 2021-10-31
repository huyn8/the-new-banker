#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <sstream> 
#include <string>
#include <vector>

using namespace std;

/*
* This class represents a Transaction in which the Bank will use
* A Transaction is used to store information about the type of
* transaction, first and last name of the client/user, fund id,
* and more
* Those info will then be used later for further processing 
*/
class Transaction
{
public:
    //CONSTRUCTORS-DESTRUCTORS
    Transaction();
    Transaction(string details);
    ~Transaction();

    //GETTERS
    string GetDetails();
    string GetType();
    string GetFirstName();
    string GetLastName();

    int GetAmount();
    int GetAccountID();
    int GetOtherAccountID();
    int GetFundID();
    int GetOtherFundID();

private:
    //INTERNAL DATA MEMBERS
    string full_details_, type_, first_, last_;
    int account_id_, other_account_id_, fund_id_, other_fund_id_, amount_;
};

#endif 