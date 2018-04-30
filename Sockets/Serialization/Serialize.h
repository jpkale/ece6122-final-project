//
// Created by Nick Dargi on 4/28/18.
//
#include <sstream>
#ifndef BANKINGAPPSERVER_SERIALIZE_H
#define BANKINGAPPSERVER_SERIALIZE_H
class Credential {
public:
    std::string username;
    std::string password;
    Credential();
    ~Credential();
};
std::string serializecredentialcreate(Credential cred);
std::string serializewithdrawl(Credential cred,double amount);
std::string serializedeposit(Credential cred,double amount);
int determineprocess(char* input);
std::string serializecredentiallogin(Credential cred);
bool determinesuccess(char* input);
double returnbalance(char* input);
double serverreturnamount(char* input);
#endif //BANKINGAPPSERVER_SERIALIZE_H
