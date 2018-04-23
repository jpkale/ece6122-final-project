#ifndef BANKINGAPPSERVER_ACCOUNT_H
#define BANKINGAPPSERVER_ACCOUNT_H

#endif //BANKINGAPPSERVER_ACCOUNT_H

//Manage account information from login credentials to balance
class accountHolder;
class account {
public:
    //Constructors:
    account();
    account(const char* accountNumber, double balance, const char* userID, const char* userPassword);
    //overloaded operators

    //member functions
    void linkAccount(const char* accountNumber, accountHolder* a); //associates account number with an account holder
    void deposit(const char* accountNumber, double depositAmount);
    void withdrawal(const char* accountNumber, double withdrawAmount);
//Data members
public:
    double balance;
    const char* accountNumber;

private:
    //hash for password encryption if needed or other private encryption data members
    const char* hash;


};