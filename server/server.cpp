#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int socketID, acceptedID, PORT;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no PORT provided\n");
        exit(1);
    }
    socketID = socket(AF_INET, SOCK_STREAM, 0);
    if (socketID < 0) {
        error("ERROR opening socket");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    PORT = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    if (bind(socketID, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    listen(socketID,5);
    clilen = sizeof(cli_addr);
    acceptedID = accept(socketID,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (acceptedID < 0) {
        error("ERROR accepting the connection");
    }
    bzero(buffer,256);
    n = read(acceptedID,buffer,255);
    if (n < 0) {
        error("ERROR reading from socket");
    }
    printf("Here is the message: %s\n",buffer);
    n = write(acceptedID,"Message Success",18);
    if (n < 0)
    {
        error("ERROR writing to socket");
    }
    close(acceptedID);
    close(socketID);
    return 0;
}