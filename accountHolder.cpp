//
// Created by Dennis on 4/24/2018.
//
#include <iostream>
#include <string>

#include "accountHolder.h"

using namespace std;

//Constructors
accountHolder::accountHolder(){
    name       = " ";
    middleInit = " ";
    lastName   = " ";
}

accountHolder::accountHolder(const char *nameU, const char *lastNameU) {
    name       = nameU;
    lastName   = lastNameU;
}

accountHolder::accountHolder(const char *nameU, const char *middleInitU, const char *lastNameU) {
    name       = nameU;
    lastName   = lastNameU;
    middleInit = middleInitU;
}

//Member functions
char* accountHolder::getFullName() const
{
    //return
}