//
// Created by Nick Dargi on 4/28/18.
//

#include "ClientFunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
int clientcreator(char *port, char *host)
{
    int socketID, PORT, classifier;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    PORT = atoi(port);
    socketID = socket(AF_INET, SOCK_STREAM, 0);
    if (socketID < 0) {
        error("ERROR opening socket");
    }
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);
    if (connect(socketID,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }
    return socketID;
}
