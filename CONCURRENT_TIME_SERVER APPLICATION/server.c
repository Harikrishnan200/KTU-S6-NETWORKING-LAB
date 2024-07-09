#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("socket creation failed");
        exit(0);
    }

    // memset(&servaddr, 0, sizeof(servaddr));
    // memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 ) {
        printf("bind failed");
        exit(0);
    }

    int len, n;

    while (1) {
        len = sizeof(cliaddr); //len is value/result

        n = recvfrom(sockfd,buffer, MAXLINE,
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                    &len);   //  MSG_WAITALL is the flag , you can also use 0 instead of it.
        buffer[n] = '\0';

        printf("Time request from client");
        puts(buffer);

        // Get current time
        time_t currentTime;
        struct tm *timeinfo;
        time(&currentTime);
        timeinfo = localtime(&currentTime);
        strftime(buffer, MAXLINE, "%Y-%m-%d %H:%M:%S", timeinfo);

        // Send time back to client
        sendto(sockfd, (char *)buffer, strlen(buffer),
            MSG_CONFIRM, (struct sockaddr *) &cliaddr,  
                len);                //  MSG_CONFIRM is the flag , you can also use 0 instead of it.
    } 

    return 0;
}

//OUTPUT
// Time request from client
