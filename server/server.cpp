
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../Sockets/CreateServer/ServerFunc.h"
#include "../Sockets/Serialization/Serialize.h"
#include <sstream>
int main(int argc, char *argv[]) {
    int socketID, n;
    bool was_successful;
    double balance;
    double amount;
    char buffer[256];
    int b = 1;
    socketID = servercreator(argv[1]);
    while(b)
    {
        bzero(buffer,256);
        n = read(socketID,buffer,255);
        int process = determineprocess(buffer);
        std::ostringstream strs;
        switch(process)
        {

            case 1: printf("Create Account");
                //Attempt to create account and set the value of was_successful.
                if (was_successful)
                {
                    n = write(socketID,"1",1);//Will Send True if successful
                }
                else
                {
                    n = write(socketID,"0",1);//Will Send False if unsuccessful
                }
            case 2: printf("Deposit");
                //Attempt to Perform Deposit of amount here and set boolean was_successful, set balance to accounts balance
                amount = serverreturnamount(buffer);
                if (was_successful)
                {
                    strs << balance;
                    std::string sendstring = "1," + strs.str() + ",";
                    strcpy(buffer,sendstring.c_str());
                    n = write(socketID,buffer,strlen(buffer));//Will Send True if successful followed by balance
                }
                else
                {
                    strs << balance;
                    std::string sendstring = "0," + strs.str() + ",";
                    strcpy(buffer,sendstring.c_str());
                    n = write(socketID,"0",1);//Will Send False if unsuccessful followed by balance
                }
            case 3: printf("Withdrawl");
                //Attempt to Perform Withdrawl here and set boolean was_successful, set balance to accounts balance
                amount = serverreturnamount(buffer);
                if (was_successful)
                {
                    strs << balance;
                    std::string sendstring = "1," + strs.str() + ",";
                    strcpy(buffer,sendstring.c_str());
                    n = write(socketID,buffer,strlen(buffer));///Will Send True if successful followed by balance
                }
                else
                {
                    strs << balance;
                    std::string sendstring = "0," + strs.str() + ",";
                    strcpy(buffer,sendstring.c_str());
                    n = write(socketID,buffer,strlen(buffer));///Will Send False if unsuccessful followed by balance
                }
            case 4: printf("Login to Account");
                //Attempt to Perform Login here and set boolean was_successful, set balance to accounts balance
                if (was_successful)
                {
                    strs << balance;
                    std::string sendstring = "1," + strs.str() + ",";
                    strcpy(buffer,sendstring.c_str());
                    n = write(socketID,buffer,strlen(buffer));///Will Send True if successful followed by balance
                }
                else
                {
                    n = write(socketID,"0",1);//Will Send False if unsuccessful
                }
        }
    }
    return 0;
}
//TESTING CODE HERE