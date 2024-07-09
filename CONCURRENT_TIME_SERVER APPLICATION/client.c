#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("socket creation failed");
        exit(0);
    }

    // memset(&servaddr, 0, sizeof(servaddr));   (optional)

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    // Send time request to server
    sendto(sockfd, "Time request sent", strlen("TIME"),
        MSG_CONFIRM, (const struct sockaddr *)&servaddr,
            sizeof(servaddr));                     //  MSG_CONFIRM is the flag , you can also use 0 instead of it.
    printf("Time request sent.\n");

    // Receive time from server
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, NULL, NULL);       //  MSG_WAITALL is the flag , you can also use 0 instead of it.
    buffer[n] = '\0';

    // Display received time
    printf("Server Time: %s\n", buffer);

    close(sockfd);
    return 0;
}

/*

OUTPUT:

Time request sent.
Server Time: 16:00:00

*/

/*

OUTPUT:

Time request sent.
Server Time: 16:00:00
    
    */