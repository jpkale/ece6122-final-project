//
// Created by Dennis on 4/24/2018.
//
#include <iostream>
#include <string>

#include "accountHolder.h"

using namespace std;

//Constructors
accountHolder::accountHolder()
{
    name       = " ";
    middleInit = " ";
    lastName   = " ";
}

accountHolder::accountHolder(const char *nameU, const char *lastNameU)
{
    name       = nameU;
    lastName   = lastNameU;
}

accountHolder::accountHolder(const char *nameU, const char *middleInitU, const char *lastNameU)
{
    name       = nameU;
    lastName   = lastNameU;
    middleInit = middleInitU;
}

//Member functions
const char* accountHolder::getFullName()
{
    string fullName = name + " " + middleInit + " " + lastName;
    return fullName.c_str();
}

const char* accountHolder::getSSN()
{
    return SSN.c_str();
}

const char* accountHolder::getAddress()
{
    return address.c_str();
}

long accountHolder::getCreditScore()
{
    return score;
}

long accountHolder::getAccount()
{
    return account;
}

void accountHolder::setAddress(const char* addressIn)
{
    address = addressIn;
}

void accountHolder::setCreditScore(long ScoreIn)
{
    score = ScoreIn;
}

void accountHolder::setSSN(const char *SSNIn)
{
    SSN = SSNIn;
}

void accountHolder::addAccount(long accountNumber)
{
    account = accountNumber;
}
