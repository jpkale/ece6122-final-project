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

account::account(long accountNumberIn, long balanceIn, const char *userIDIn, const char *userPasswordIn)
{
    accountNumber = accountNumberIn;
    balance = balanceIn;
    userID = userIDIn;
    userPassword = userPasswordIn;
}

void account::deposit(long accountNumber, long depositAmount)
{
    balance += depositAmount;
}

void account::withdrawal(long accountNumber, long withdrawAmount)
{
    balance -= withdrawAmount;
}

void account::linkAccount(long accountNumber, accountHolder a)
{
    a.addAccount(accountNumber);
}
