#ifndef BANKINGAPPSERVER_ACCOUNT_H
#define BANKINGAPPSERVER_ACCOUNT_H

#endif //BANKINGAPPSERVER_ACCOUNT_H

//Manage account information from login credentials to balance
class accountHolder;
class account {
public:
    //Constructors:
    account();
    account(double accountNumber, double balance, const char* userID, const char* userPassword);
    //overloaded operators

    //member functions
    void linkAccount(double accountNumber, accountHolder* a); //associates account number(s) with an account holder
    void deposit(double accountNumber, double depositAmount);
    void withdrawal(double accountNumber, double withdrawAmount);
//Data members
public:
    double balance;
    double accountNumber;

private:
    //key for password encryption if needed or other private encryption data members
    const char* key;
    const char* userPassword;

};