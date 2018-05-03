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
    account(long accountNumberIn, long balanceIn, const char* userIDIn, const char* userPasswordIn);
    //overloaded operators

    //member functions
    void linkAccount(long accountNumber, accountHolder a); //associates account number(s) with an account holder
    void deposit(long accountNumber, long depositAmount);
    void withdrawal(long accountNumber, long withdrawAmount);
//Data members
public:
    long balance;
    long accountNumber;
    std::string userID;

private:
    //key for password encryption if needed or other private encryption data members
    std::string key;
    std::string userPassword;

};

#endif //BANKINGAPPSERVER_ACCOUNT_H
