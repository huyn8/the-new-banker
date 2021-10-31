#include "Transaction.h"

Transaction::Transaction()
{
    //Default
}

// The whole point of this constructor is for a Transaction to initilize its data members
// A Transaction can be broken up into smaller details which can be utilized by other classes,
// thus, this constructor will break up a Transaction into smaller, usable pieces of information
Transaction::Transaction(string details)
{
    full_details_ = details;

    //The following steps will break a Transaction into smaller details
    vector <string> tokens;
    stringstream ss(details);  
    string str;

    while (getline(ss, str, ' ')) {
        tokens.push_back(str);
    }

    if(tokens[0] == "O")
    {
        type_ = tokens[0];
        first_ = tokens[1];
        last_ = tokens[2];
        account_id_ = stoi(tokens[3]);//converting string to number
    }

    else if(tokens[0] == "D" || tokens[0] == "W") 
    {
        type_ = tokens[0];
        account_id_ = stoi(tokens[1].substr(0,4));
        fund_id_ = stoi(tokens[1].substr(4));
        amount_ = stoi(tokens[2]);
    }

    else if(tokens[0] == "T")
    {
        type_ = tokens[0];
        account_id_ = stoi(tokens[1].substr(0,4));
        fund_id_ = stoi(tokens[1].substr(4));
        amount_ = stoi(tokens[2]);
        other_account_id_ = stoi(tokens[3].substr(0,4));
        other_fund_id_ = stoi(tokens[3].substr(4));
    }

    //History  
    else
    {
        type_ = tokens[0];
        account_id_ = stoi(tokens[1].substr(0,4));

        if(tokens[1].length() == 5)
        {
            fund_id_ = stoi(tokens[1].substr(4));
        }
        else
        {
            fund_id_ = -1;
        }
        
    }
}

Transaction::~Transaction()
{
    //Destructor
}

//GETTERS
string Transaction::GetDetails()
{
    return full_details_;
}

string Transaction::GetType()
{
    return type_;
}

string Transaction::GetFirstName()
{
    return first_;
}
 
string Transaction::GetLastName()
{
    return last_;
}

int Transaction::GetAmount()
{
    return amount_;
}
    
int Transaction::GetAccountID()
{
    return account_id_;
}

int Transaction::GetOtherAccountID()
{
    return other_account_id_;
}

int Transaction::GetFundID()
{
    return fund_id_;
}

int Transaction::GetOtherFundID()
{
    return other_fund_id_;
}