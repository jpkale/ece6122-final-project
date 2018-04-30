//
// Created by Nick Dargi on 4/28/18.
//
#include <sstream>
#include "../../client/ui/landing.h"
#ifndef BANKINGAPPSERVER_SERIALIZE_H
#define BANKINGAPPSERVER_SERIALIZE_H

std::string serializecredentialcreate(ui::Credential* cred);
std::string serializewithdrawl(ui::Credential* cred,double amount);
std::string serializedeposit(ui::Credential* cred,double amount);
int determineprocess(char* input);
std::string serializecredentiallogin(ui::Credential* cred);
bool determinesuccess(char* input);
double returnbalance(char* input);
double serverreturnamount(char* input);
std::string serverreturnpassword(char* input);
std::string serverreturnusername(char* input);
#endif //BANKINGAPPSERVER_SERIALIZE_H
