#ifndef BANKINGAPPSERVER_ACCOUNT_H
#define BANKINGAPPSERVER_ACCOUNT_H

#include <string>
#include "accountHolder.h"

//Manage account information from login credentials to balance
class accountHolder;
class account {
public:
    //Constructors:
    account();
    account(double accountNumberIn, double balanceIn, const char* userIDIn, const char* userPasswordIn);
    //overloaded operators

    //member functions
    void linkAccount(double accountNumber, accountHolder a); //associates account number(s) with an account holder
    void deposit(double accountNumber, double depositAmount);
    void withdrawal(double accountNumber, double withdrawAmount);
//Data members
public:
    double balance;
    double accountNumber;
    std::string userID;

private:
    //key for password encryption if needed or other private encryption data members
    std::string key;
    std::string userPassword;

};

#endif //BANKINGAPPSERVER_ACCOUNT_H