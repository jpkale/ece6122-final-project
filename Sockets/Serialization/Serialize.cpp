//
// Created by Nick Dargi on 4/28/18.
//

#include "Serialize.h"
#include <sstream>
std::string serializecredentialcreate(ui::Credential* cred)
{
    std::string output = "1,"+cred->username +"," + cred->password + ",";
    return output;
}
std::string serializedeposit(ui::Credential* cred,long amount)
{
    std::ostringstream strs;
    strs << amount;
    std::string output = "2,"+cred->username +"," + cred->password +"," + strs.str() + ",";
    return output;
}
std::string serializewithdrawl(ui::Credential* cred,long amount)
{
    std::ostringstream strs;
    strs << amount;
    std::string output = "3,"+cred->username +"," + cred->password + "," + strs.str() + ",";
    return output;
}
int determineprocess(char* input)
{
    int output;
    output = (int)input[0] - 48;
    return output;
}

std::string serializecredentiallogin(ui::Credential* cred)
{
    std::string output = "4,"+cred->username +"," + cred->password + ",";
    return output;
}

bool determinesuccess(char* input)
{
    return input[0] == '1';
}

long returnbalance(char* input)
{
    long balance;
    std::string placeholder;
    for(int i = 2;i<256;i++)
    {
        if (input[i] < '0' || input[i] > '9' )
            continue;
        placeholder.push_back(input[i]);
    }

    balance = std::stol(placeholder);
    return balance;
}
long serverreturnamount(char* input)
{
    long balance;
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
std::string serverreturnusername(char* input)
{
    long balance;
    int j = 0;
    std::string placeholder;
    for(int i = 2;i<256;i++)
    {
        if(input[i] == 44)
        {
            j++;
            if(j == 1)
            {
                break;
            }
        }
        else
        {
                placeholder.push_back(input[i]);
        }
    }
    return placeholder;
}
std::string serverreturnpassword(char* input)
{
    long balance;
    int j = 0;
    std::string placeholder;
    for(int i = 2;i<256;i++)
    {
        if(input[i] == 44)
        {
            j++;
            if(j == 2)
            {
                break;
            }
        }
        else
        {
            if (j == 1) {
                placeholder.push_back(input[i]);
            }
        }
    }
    return placeholder;
}
