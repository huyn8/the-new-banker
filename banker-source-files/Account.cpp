#include "Account.h"

Account::Account()
{
    //Default
}

Account::Account(int id)
{
    id_ = id;
    CreateFunds();
}

Account::Account(int id, string first, string last)
{
    id_ = id;
    first_name_ = first;
    last_name_ = last;
    CreateFunds();
}

Account::~Account()
{
    //Destructor
}

void Account::CreateFunds()
{
    Fund fund1(0, "Money Market", 1);
    Fund fund2(1, "Prime Money Market", 0);
    Fund fund3(2, "Long-Term Bond", 3);
    Fund fund4(3, "Short-Term Bond", 2);
    Fund fund5(4, "500 Index Fund");
    Fund fund6(5, "Capital Value Fund");
    Fund fund7(6, "Growth Equity Fund");
    Fund fund8(7, "Growth Index Fund");
    Fund fund9(8, "Value Fund");
    Fund fund10(9, "Value Stock Index");

    funds_.push_back(fund1);
    funds_.push_back(fund2);
    funds_.push_back(fund3);
    funds_.push_back(fund4);
    funds_.push_back(fund5);
    funds_.push_back(fund6);
    funds_.push_back(fund7);
    funds_.push_back(fund8);
    funds_.push_back(fund9);
    funds_.push_back(fund10);
}

bool Account::Deposit(int amount, int fundID, string transactionHistory)
{
    //negative amount
    if(amount < 0)
    {
        cout << "\nERROR: Negative amount is not allowed" << endl;
        RecordFundHistory(transactionHistory + "(failed)", fundID);
        return false;
    }

    else if(amount >= 0)
    {
        funds_[fundID].SetBalance(amount);
        RecordFundHistory(transactionHistory, fundID);
        return true;
    }

    return false;
}

bool Account::WithDraw(int amount, int fundID, string transactionHistory)
{
    //negative amount
    if(amount < 0)
    {      
        cout << "\nERROR: Negative amount is not allowed" << endl;
        RecordFundHistory(transactionHistory + "(failed)", fundID);
        return false;
    }

    else if(amount <= funds_[fundID].GetBalance())
    {
        funds_[fundID].SetBalance((-amount));
        RecordFundHistory(transactionHistory, fundID);
        return true;
    }

    if(amount > funds_[fundID].GetBalance() 
    && funds_[fundID].isLinked()
    && amount <= (funds_[fundID].GetBalance() + 
    funds_[funds_[fundID].GetLinkedFundID()].GetBalance()))
    {
        //Setting balance for current fund
        transactionHistory = "W " + to_string(GetID()) + 
        to_string(fundID) + " " + to_string(funds_[fundID].GetBalance());
        funds_[fundID].SetBalance((-amount));
        RecordFundHistory(transactionHistory, fundID);

        //Getting the missing amount and linked Fund's id
        int missingAmount = -(funds_[fundID].GetBalance());
        int linkedFundID = funds_[fundID].GetLinkedFundID();

        //Use the missing amount in linked Fund to compensate
        if(missingAmount <=  funds_[linkedFundID].GetBalance())
        {
            funds_[linkedFundID].SetBalance(-missingAmount);
            funds_[fundID].SetBalance(missingAmount);

            transactionHistory = "W " + to_string(GetID()) + 
            to_string(linkedFundID) + " " + to_string(missingAmount);

            RecordFundHistory(transactionHistory, linkedFundID);
            return true;
        }
        else
        {
            cout << "\nERROR: Not enough funds to withdraw " << amount 
            << " from " << GetFirstName() 
            << " " << GetLastName() << " " 
            << funds_[fundID].GetName() << " and "
            << "linked fund " << funds_[linkedFundID].GetName() << endl;
            if(transactionHistory != "")
            {
                RecordFundHistory(transactionHistory + "(failed)", linkedFundID);
            }
        }
    }
    else
    {
        cout << "\nERROR: Not enough funds to withdraw " << amount 
        << " from " << GetFirstName() 
        << " " << GetLastName() << " " 
        << funds_[fundID].GetName() << endl;
        if(transactionHistory != "")
        {
            RecordFundHistory(transactionHistory + "(failed)", fundID);
        }   
    }
    return false;
}

bool Account::Transfer(int amount, int fromFundID, Account &toAccount, int toFundID, string transactionHistory)
{
    //negative amount
    if(amount < 0)
    {
        cout << "\nERROR: Negative amount is not allowed" << endl;
        RecordFundHistory(transactionHistory + "(failed)", fromFundID);
        return false;
    }

    //transfering to the same fund in the same account
    if((GetID() == toAccount.GetID()) && fromFundID == toFundID)
    {
        cout << "\nERROR: Cannot transfer from and to the same fund" << endl;
        RecordFundHistory(transactionHistory + "(failed)", fromFundID);
        return false;
    }
    //otherwise, proceed
    else if(WithDraw(amount, fromFundID, ""))
    {    
        if(toAccount.Deposit(amount, toFundID, ""))
        {
            RecordFundHistory(transactionHistory, fromFundID);
            toAccount.RecordFundHistory(transactionHistory, toFundID);
            return true;
        }
    }
    else
    {        
        cout << "\nERROR: Tranfering failed" << endl;
        RecordFundHistory(transactionHistory + "(failed)", fromFundID);
    }
    return false;
}

void Account::RecordHistory(string transactionHistory)
{
    if(transactionHistory != "")
    {
        transaction_history_.push(transactionHistory);
    }
}

void Account::RecordFundHistory(string transactionHistory, int fundID)
{
    if(transactionHistory != "")
    {
        funds_[fundID].RecordHistory(transactionHistory);
    }
}

//GETTERS
void Account::History(string transactionHistory)
{
    cout << "\nTransaction History for " << GetFirstName() 
    << " " << GetLastName() << " by fund: " << endl;
    for(int i = 0; i < funds_.size(); i++)
    {
        if(funds_[i].hasHistory())
        {
            cout << funds_[i].GetName() << ": $" << funds_[i].GetBalance() << endl;
            funds_[i].GetHistory();
        }
    }
    return;
}

void Account::FundHistory(int fundID)
{
    cout << "\nTransaction History for " << GetFirstName() 
    << " " << GetLastName() << " " 
    <<  funds_[fundID].GetName() << ": $" 
    <<  funds_[fundID].GetBalance() << endl;
    funds_[fundID].GetHistory();
}

int Account::GetBalance() const
{
    double total = 0;
    for(int i = 0; i < funds_.size(); i++)
    {
        total += funds_[i].GetBalance();
    }
    return total;
}

int Account::GetFundBalance(int fundID) const
{
    return funds_[fundID].GetBalance();
}

string Account::GetFundName(int fundID) const
{
    return funds_[fundID].GetName();
}

string Account::GetFirstName() const
{
    return first_name_;
} 

string Account::GetLastName() const
{
    return last_name_;
}

int Account::GetID() const
{
    return id_;
}