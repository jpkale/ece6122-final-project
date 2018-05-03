#include <iostream>
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
#include "../server/log.h"
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: ./BankingAppServer [PORT]" << endl;
        exit(-1);
    }

    int socketID, n;
    bool was_successful = false;
    long balance;
    long amount;
    std::string passCheck;
    char buffer[256];
    int b = 1;
    socketID = servercreator(argv[1]);
    std::string username;
    std::string password;

    while(b)
    {
        bzero(buffer,256);
        n = read(socketID,buffer,255);
        int process = determineprocess(buffer);
        was_successful = false;
        std::ostringstream strs;
        switch(process)
        {

            case 1: {
                printf("Create Account\n");
                was_successful = false;
                //Attempt to create account and set the value of was_successful.
                username = serverreturnusername(buffer);
                password = serverreturnpassword(buffer);
                was_successful = log::createFile(username, password);
                if (was_successful) {
                    n = write(socketID, "1", 1);//Will Send True if successful
                } else {
                    n = write(socketID, "0", 1);//Will Send False if unsuccessful
                }
                break;
            }
            case 2: {
                printf("Deposit\n");
                amount = serverreturnamount(buffer);
                long previous_balance = log::getBalance(username, password);
                long new_balance = previous_balance + amount;
                log::writeFile(username, password, new_balance, amount, DEPOSIT);
                strs << new_balance;
                std::string sendstring = "1," + strs.str() + ",";
                strcpy(buffer, sendstring.c_str());
                n = write(socketID, buffer, strlen(buffer));
                break;
            }
            case 3: {
                printf("Withdrawl\n");

                //Attempt to Perform Withdrawl here and set boolean was_successful, set balance to accounts balance
                amount = serverreturnamount(buffer);
                long oldbalance = log::getBalance(username, password);

                if (oldbalance >= amount) {
                    long newamount = log::getBalance(username, password) - amount;
                    log::writeFile(username, password, newamount, amount, WITHDRAW);
                    strs << newamount;
                    std::string sendstring = "1," + strs.str() + ",";
                    strcpy(buffer, sendstring.c_str());
                } else {
                    strs << oldbalance;
                    std::string sendstring = "0," + strs.str() + ",";
                    strcpy(buffer, sendstring.c_str());
                }
                printf("Buffer: %s\n", buffer);
                n = write(socketID, buffer, strlen(buffer));///Will Send False if unsuccessful followed by balance
                break;
            }
            case 4: {
                printf("Login to Account\n");

                //Attempt to Perform Login here and set boolean was_successful, set balance to accounts balance
                username = serverreturnusername(buffer);
                password = serverreturnpassword(buffer);
                passCheck = log::getPassword(username, password);
                was_successful = false;
                if (passCheck == password) {
                    was_successful = true;
                }
                if (was_successful) {
                    log::openLog(username, password);
                    balance = log::getBalance(username, password);
                    strs << balance;
                    std::string sendstring = "1," + strs.str() + ",";
                    strcpy(buffer, sendstring.c_str());
                    n = write(socketID, buffer, strlen(buffer));///Will Send True if successful followed by balance
                } else {
                    n = write(socketID, "0", 1);//Will Send False if unsuccessful
                }
                break;
            }
        }
    }
    return 0;
}
