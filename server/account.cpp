//
// Created by Dennis on 4/24/2018.
//

#include <iostream>
#include <string>

#include "account.h"
#include "accountHolder.h"
#include <string>

using namespace std;

account::account()
{
    accountNumber = 0;
    balance = 0;
    userID = " ";
    userPassword = " ";
}

account::account(double accountNumberIn, double balanceIn, const char *userIDIn, const char *userPasswordIn)
{
    accountNumber = accountNumberIn;
    balance = balanceIn;
    userID = userIDIn;
    userPassword = userPasswordIn;
}

void account::deposit(double accountNumber, double depositAmount)
{
    balance += depositAmount;
}

void account::withdrawal(double accountNumber, double withdrawAmount)
{
    balance -= withdrawAmount;
}

void account::linkAccount(double accountNumber, accountHolder a)
{
    a.addAccount(accountNumber);
}

double account::checkCredentials(const char *userIDIn, const char *userPasswordIn)
{
    double falseAccount = 0;
    if (userIDIn == userID && userPasswordIn == userPassword)
    {
        return accountNumber;
    }
    else return falseAccount;
}