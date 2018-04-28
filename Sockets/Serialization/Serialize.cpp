//
// Created by Nick Dargi on 4/28/18.
//

#include "Serialize.h"
#include <sstream>
std::string serializecredentialcreate(Credential cred)
{
    std::string output = "1,"+cred.username +"," + cred.password;
    return output;
}
std::string serializedeposit(Credential cred,double amount)
{
    std::ostringstream strs;
    strs << amount;
    std::string output = "2,"+cred.username +"," + cred.password +"," + strs.str();
    return output;
}
std::string serializewithdrawl(Credential cred,double amount)
{
    std::ostringstream strs;
    strs << amount;
    std::string output = "3,"+cred.username +"," + cred.password + "," + strs.str();
    return output;
}
int determineprocess(char* input)
{
    int output;
    output = (int)input[0] - 48;
    return output;
}
std::string serializecredentiallogin(Credential cred)
{
    std::string output = "4,"+cred.username +"," + cred.password;
    return output;
}
bool determinesuccess(char* input)
{
    int success = (int)input[0] - 48;
    if(success == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}