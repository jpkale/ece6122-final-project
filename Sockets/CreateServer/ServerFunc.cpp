//
// Created by Nick Dargi on 4/28/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "ServerFunc.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int servercreator(char *port) //Function returns the server socketID which can be used to send and receive messages on the port.
{
    int socketID, accepted, PORT;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    socketID = socket(AF_INET, SOCK_STREAM, 0);
    if (socketID < 0) {
        error("ERROR opening socket");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    PORT = atoi(port);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    if (bind(socketID, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    listen(socketID,5);
    clilen = sizeof(cli_addr);
    accepted = accept(socketID,
                      (struct sockaddr *) &cli_addr,
                      &clilen);
    if (accepted < 0) {
        error("ERROR accepting the connection");
    }
    return accepted;
}
