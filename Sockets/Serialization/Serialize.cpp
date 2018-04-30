//
// Created by Nick Dargi on 4/28/18.
//

#include "Serialize.h"
#include <sstream>
std::string serializecredentialcreate(Credential cred)
{
    std::string output = "1,"+cred.username +"," + cred.password + ",";
    return output;
}
std::string serializedeposit(Credential cred,double amount)
{
    std::ostringstream strs;
    strs << amount;
    std::string output = "2,"+cred.username +"," + cred.password +"," + strs.str() + ",";
    return output;
}
std::string serializewithdrawl(Credential cred,double amount)
{
    std::ostringstream strs;
    strs << amount;
    std::string output = "3,"+cred.username +"," + cred.password + "," + strs.str() + ",";
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
    std::string output = "4,"+cred.username +"," + cred.password + ",";
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
double returnbalance(char* input)
{
    double balance;
    std::string placeholder;
    for(int i = 2;i<256;i++)
    {
        if(input[i] == 44)
        {
            break;
        }
        else
        {
            placeholder.push_back(input[i]);
        }
    }
    balance = std::stod(placeholder);
    return balance;
}
double serverreturnamount(char* input)
{
    double balance;
    int j = 0;
    std::string placeholder;
    for(int i = 2;i<256;i++)
    {
        if(input[i] == 44)
        {
            j++;
            if(j == 3)
            {
                break;
            }
        }
        else
        {
            if (j == 2) {
                placeholder.push_back(input[i]);
            }
        }
    }
    balance = std::stod(placeholder);
    return balance;
}