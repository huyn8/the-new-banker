#include "Bank.h"
#include <string>
#include <iostream>

using namespace std;
/*
* This Driver represents a client-side interaction with the Bank
* The client/user will use the Bank by giving an appropriate input txt file
*/
int main()
{
    Bank AmazingBank("Amazing Bank");

    if(AmazingBank.Execute("BankTransIn.txt"))
    {
        
        cout << "Executed sucessfully" << endl;
    }

    else
    {
        cout << "Executed unsucessfully" << endl;
    }

    return 0;
}