#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT_NO 5000
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr)); // memory bolck intialization
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_NO);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    strcpy(buffer, "Hello, Server!");
    send(sockfd, buffer, strlen(buffer), 0);
    printf("Message sent\n");

    memset(buffer, 0, sizeof(buffer));
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("Received: %s\n", buffer);

    close(sockfd);
    return 0;
}


/*
gcc -o client client.c
./client

*/