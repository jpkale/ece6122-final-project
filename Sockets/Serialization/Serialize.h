//
// Created by Nick Dargi on 4/28/18.
//
#include <sstream>
#include "../../client/ui/landing.h"
#ifndef BANKINGAPPSERVER_SERIALIZE_H
#define BANKINGAPPSERVER_SERIALIZE_H

std::string serializecredentialcreate(ui::Credential* cred);
std::string serializewithdrawl(ui::Credential* cred,long amount);
std::string serializedeposit(ui::Credential* cred,long amount);
int determineprocess(char* input);
std::string serializecredentiallogin(ui::Credential* cred);
bool determinesuccess(char* input);
long returnbalance(char* input);
long serverreturnamount(char* input);
std::string serverreturnpassword(char* input);
std::string serverreturnusername(char* input);
#endif //BANKINGAPPSERVER_SERIALIZE_H
