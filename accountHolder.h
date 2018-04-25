#ifndef BANKINGAPPSERVER_ACCOUNTHOLDER_H
#define BANKINGAPPSERVER_ACCOUNTHOLDER_H

#endif //BANKINGAPPSERVER_ACCOUNTHOLDER_H

class account;

class accountHolder{
public:
    //Constructors:
    accountHolder();
    accountHolder(const char* nameU, const char* middleInitU, const char* lastNameU);
    explicit accountHolder(const char* nameU, const char* lastNameU);  //define account holder only by name
    //Member functions
    char* getFullName()          const;     //Returns the full name of the account holder
    char* getAddress()           const;     //Returns the address of the account holder
    char* getSSN()               const;     //Returns the SSN of the account holder
    double      getCreditScore() const;     //Returns the credit score of the account holder
    double*     getAccounts()    const;     //Returns the account numbers associated with this holder
    void addAccount(double accountnumber);  //Adds an additional account associated with the account holder
    //Set Personal information functions
    void setAddress(const char* address);
    void setSSN(const char* SSN);
    void setCreditScore(double Score);
    void setAccounts(double* arrayAccounts);

private:
    const char* name;
    const char* middleInit;
    const char* lastName;
    const char* address;
    const char* SSN;
    double Score;
    double* arrayAccounts;

};