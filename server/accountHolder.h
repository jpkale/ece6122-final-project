#ifndef BANKINGAPPSERVER_ACCOUNTHOLDER_H
#define BANKINGAPPSERVER_ACCOUNTHOLDER_H

#include <string>

//class account;

class accountHolder{
public:
    //Constructors:
    accountHolder();
    accountHolder(const char* nameU, const char* middleInitU, const char* lastNameU);
    explicit accountHolder(const char* nameU, const char* lastNameU);  //define account holder only by name and last name
    //Member functions
    const char* getFullName();                //Returns the full name of the account holder
    const char* getAddress();                 //Returns the address of the account holder
    const char* getSSN();                     //Returns the SSN of the account holder
    long getCreditScore();                  //Returns the credit score of the account holder
    long getAccount();                      //Returns the account number associated with this holder
    void addAccount(long accountNumber);    //Adds an account associated with the account holder
    //Set Personal information functions
    void setAddress(const char* addressIn);
    void setSSN(const char* SSNIn);
    void setCreditScore(long ScoreIn);

private:
    std::string name;
    std::string middleInit;
    std::string lastName;
    std::string address;
    std::string SSN;
    long score;
    long account;

};

#endif //BANKINGAPPSERVER_ACCOUNTHOLDER_H
