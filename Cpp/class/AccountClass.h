#ifndef ACCOUNTCLASS_H
#define ACCOUNTCLASS_H
#include <iostream>
#include <iomanip>
using namespace::std;

class Account
{
    private:
    static float Rate;
    static int Count;
    int Balance;
    char Id[20];

    public:
    Account();
    Account(char[]);
    Account(char[], int);
    ~Account();
    void Deposit(int);
    void WithDraw(int);
    void CheckBalance() const;

    void CheckRate() const {cout << "Rate : " << Rate << "%" << endl; }
    void CheckCount() const;
};

inline void Account::Deposit(int CashInput)
{
    Balance += CashInput;
    cout << setw(8) << Id << "Deposit " << endl;
    cout << "Balance : " << Balance << endl;
    return;
}

inline void Account::CheckBalance() const
{
    cout << setw(8) << Id << " balance : " << Balance << endl;
    return;
}



#endif