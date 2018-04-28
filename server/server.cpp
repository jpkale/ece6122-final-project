
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../Sockets/CreateServer/ServerFunc.h";
#include "../Sockets/Serialization/Serialize.h";
#include <sstream>
// Placeholder for now
int main(int argc, char *argv[]) {
    int socketID, n;
    bool was_successful;
    double balance;
    char buffer[256];
    socketID = servercreator(argv[1]);
    while(1)
    {
        bzero(buffer,256);
        n = read(socketID,buffer,255);
        int process = determineprocess(buffer);
        switch(process)
        {
            std::ostringstream strs;
            case 1: printf("Create Account");
                was_successful = determinesuccess(buffer);
                if (was_successful)
                {
                    n = write(socketID,"1",1);//Will Send True if successful
                }
                else
                {
                    n = write(socketID,"0",1);//Will Send False if unsuccessful
                }
            case 2: printf("Deposit");
                was_successful = determinesuccess(buffer);
                if (was_successful)
                {
                    strs << balance;
                    std::string sendstring = "1," + strs.str();
                    strcpy(buffer,sendstring.c_str());
                    n = write(socketID,buffer,strlen(buffer));//Will Send True if successful followed by balance
                }
                else
                {
                    strs << balance;
                    std::string sendstring = "0," + strs.str();
                    strcpy(buffer,sendstring.c_str());
                    n = write(socketID,"0",1);//Will Send False if unsuccessful followed by balance
                }
            case 3: printf("Withdrawl");
                was_successful = determinesuccess(buffer);
                if (was_successful)
                {
                    strs << balance;
                    std::string sendstring = "1," + strs.str();
                    strcpy(buffer,sendstring.c_str());
                    n = write(socketID,buffer,strlen(buffer));///Will Send True if successful followed by balance
                }
                else
                {
                    strs << balance;
                    std::string sendstring = "0," + strs.str();
                    strcpy(buffer,sendstring.c_str());
                    n = write(socketID,buffer,strlen(buffer));///Will Send False if unsuccessful followed by balance
                }
            case 4: printf("Login to Account");
                was_successful = determinesuccess(buffer);
                if (was_successful)
                {
                    strs << balance;
                    std::string sendstring = "1," + strs.str();
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