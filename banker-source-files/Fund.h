#ifndef FUND_H
#define FUND_H

#include <string>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;
/*
* This class represents a Fund in which an Account will use
* A Fund is responsible for storing information about a Fund within
* an Account
* There are mostly setters and getters for changing the data/state of
* a Fund
* Some Funds are specifically linked and some are not
* Linked Funds have their balances connected
*/
class Fund
{
public:
    //CONSTRUCTORS-DESTRUCTORS
    Fund(int fundID, string fundName);
    Fund(int fundID, string fundName, int linkedFundID);
    ~Fund();

    //GETTERS
    int GetBalance() const;
    int GetID() const;
    int GetLinkedFundID() const;
    bool isLinked() const;
    bool hasHistory();
    string GetName() const;
    void GetHistory();
    void RecordHistory(string transactionHistory);

    //SETTER
    void SetBalance(double amount);

    private:
    //INTERNAL DATA MEMBERS
    int fund_id_;
    int linked_fund_id_;
    double balance_;
    bool linked_;
    bool has_history_;

    string fund_name_;

    queue <string> transaction_history_;
};

#endif 