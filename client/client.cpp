#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include "../Sockets/CreateClient/ClientFunc.h"
#include "../Sockets/Serialization/Serialize.h"
#include "ui/landing.h"
#include "ui/home.h"
#include "ui/page.h"

using namespace ui;
using namespace std;

int socketID;
char buffer[256];
struct LoginResult {
    double balance;
    bool was_successful;
    LoginResult() : balance(0), was_successful(false) {};
    LoginResult(double balance, bool was_successful) :
        balance(balance), was_successful(was_successful) {};
};
void error(const char *msg)
{
    perror(msg);
    exit(0);
}
/*
 * Given a credential, log into the server.  Return the a LoginResult with the
 * account balance and was_successful=true if login was successful, and
 * was_successful=false if the login was not successful (balance will be
 * ignored in this case).
 */
LoginResult login(Credential* cred) {
    int classifier;
    bool was_successful;
    bzero(buffer,256);
    std::string serializeddata = serializecredentiallogin(cred);
    strcpy(buffer,serializeddata.c_str());
    classifier = write(socketID,buffer,strlen(buffer));
    if (classifier < 0) {
        error("ERROR with connection to Server");
    }
    bzero(buffer,256);
    classifier = read(socketID,buffer,255);
    if (classifier < 0) {
        error("ERROR with connection to Server");
    }
    was_successful = determinesuccess(buffer);
    double balance = returnbalance(buffer);
    return LoginResult(balance, was_successful);
}

/*
 * Given a credential, create a new account on the server.  Return true if
 * creation was successful (i.e. the account name does not already exist), or
 * false if unsuccessful.
 */
bool create_account(Credential* cred) {
    int classifier;
    bool was_successful;
    bzero(buffer,256);
    std::string serializeddata = serializecredentialcreate(cred);
    strcpy(buffer,serializeddata.c_str());
    classifier = write(socketID,buffer,strlen(buffer));
    if (classifier < 0) {
        error("ERROR with connection to Server");
    }
    bzero(buffer,256);
    classifier = read(socketID,buffer,255);
    if (classifier < 0) {
        error("ERROR with connection to Server");
    }
    was_successful = determinesuccess(buffer);
    return was_successful;
}

struct TransactionResult {
    double remaining_balance;
    bool was_successful;
    TransactionResult() : remaining_balance(0), was_successful(false) {};
    TransactionResult(double remaining_balance, bool was_successful) : 
        remaining_balance(remaining_balance), was_successful(was_successful) {};
};

/*
 * Given a credential and an amount, deposit that amount of money into the
 * account.  Amount should always be positive, but may have more than 2
 * trailing digits.  Returns the amount currently in the account and whether or
 * not the transaction was successful.
 */
TransactionResult deposit(Credential* cred, double amount) {
    int classifier;
    bool was_successful;
    bzero(buffer,256);
    std::string serializeddata = serializedeposit(cred,amount);
    strcpy(buffer,serializeddata.c_str());
    classifier = write(socketID,buffer,strlen(buffer));
    if (classifier < 0) {
        error("ERROR with connection to Server");
    }
    bzero(buffer,256);
    classifier = read(socketID,buffer,255);
    if (classifier < 0) {
        error("ERROR with connection to Server");
    }
    was_successful = determinesuccess(buffer);
    double balance = returnbalance(buffer);
    return TransactionResult(was_successful, balance);
}

/*
 * Given a credential and an amount, withdrawal that amount of money from the
 * account.  Amount should always be postive, but may have more than 2 trailing
 * digits.  Returns the amount left in the account and whether or not the
 * transaction was succesful. 
 */
TransactionResult withdrawal(Credential* cred, double amount) {
    int classifier;
    bool was_successful;
    bzero(buffer,256);
    std::string serializeddata = serializewithdrawl(cred,amount);
    strcpy(buffer,serializeddata.c_str());
    classifier = write(socketID,buffer,strlen(buffer));
    if (classifier < 0) {
        error("ERROR with connection to Server");
    }
    bzero(buffer,256);
    classifier = read(socketID,buffer,255);
    if (classifier < 0) {
        error("ERROR with connection to Server");
    }
    was_successful = determinesuccess(buffer);
    double balance = returnbalance(buffer);
    return TransactionResult(was_successful, balance);
}

void handle_login(LandingPage* lp, Credential* cred) {
    LoginResult login_r = login(cred);
    TransactionResult res;

    if (login_r.was_successful) {
        lp->popup("Welcome %s!\nYour balance is %.2lf\n",
                cred->username.c_str(),
                login_r.balance);
        
        while (true) {
            HomePage* hp = new HomePage();
            HomeResult* hr = hp->wait_for_result();
            if (hr->type == DEPOSIT) {
                res = deposit(cred, hr->amount);
                if (res.was_successful)
                    hp->popup("Depositing %.2lf was unsuccessful.\nCurrent Balance is %.2lf.\n",
                            hr->amount,
                            res.remaining_balance);
                else
                    hp->popup("Successfully deposited %.2lf!\nCurrent balance is %.2lf.\n", 
                            hr->amount,
                            res.remaining_balance);

            }
            else {
                res = withdrawal(cred, hr->amount);
                if (!res.was_successful)
                    hp->popup("Withdrawaling %.2lf was unsuccessful.\nYou only have %.2lf in your account",
                            hr->amount,
                            res.remaining_balance);
                else
                    hp->popup("Successfully withdrew %.2lf!\nYou have %.2lf remaining in your account",
                            hr->amount,
                            res.remaining_balance);
            }
        }
    }
    else
        lp->popup("Failed logging in with '%s'.\n", cred->username.c_str());
}

void handle_create_account(LandingPage* lp, Credential* cred) {
    bool create_r = create_account(cred);
    if (create_r)
        lp->popup("Welcome %s!\nPlease continue and login.",
                cred->username.c_str());
    else
        lp->popup("Sorry, '%s' is already taken.\nTry another username.\n",
                cred->username.c_str());
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Usage: ./BankingAppClient [SERVER-HOST] [SERVER-PORT]" << endl;
        exit(-1);
    }
    socketID = clientcreator(argv[2],argv[1]);
    LandingPage* lp = new LandingPage();
    LandingResult* lr = lp->wait_for_result();

    while (lr->type == CREATE) {
        handle_create_account(lp, lr->cred);
        delete lp, lr;
        lp = new LandingPage();
        lr = lp->wait_for_result();
    }

    handle_login(lp, lr->cred);
    delete lp, lr;
}
