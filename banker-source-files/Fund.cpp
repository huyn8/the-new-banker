#include "Fund.h"

Fund::Fund(int fundID, string fundName)
{
    fund_id_ = fundID;
    fund_name_ = fundName;
    linked_ = false;
    balance_ = 0;
}

Fund::Fund(int fundID, string fundName, int linkedFundID)
{
    fund_id_ = fundID;
    fund_name_ = fundName;
    linked_fund_id_ = linkedFundID;
    linked_ = true;
    balance_ = 0;
}

Fund::~Fund()
{
    //Destructor
}

int Fund::GetBalance() const
{
    return balance_;
}

int Fund::GetID() const
{
    return fund_id_;
}

int Fund::GetLinkedFundID() const
{
    return linked_fund_id_;
}

string Fund::GetName() const
{
    return fund_name_;
}

bool Fund::isLinked() const
{
    return linked_;
}

bool Fund::hasHistory()
{
    if(transaction_history_.size() != 0)
    {
        return true;
    }
    return false;
}


void Fund::GetHistory()
{
    queue <string> copy = transaction_history_;

    while (!copy.empty()){
		cout << "   " << copy.front() << endl;
		copy.pop();
	}
    return;
}

void Fund::RecordHistory(string transactionHistory)
{
    transaction_history_.push(transactionHistory);
}

void Fund::SetBalance(double amount)
{
    balance_ += amount;
}