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
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    // Send time request to server
    sendto(sockfd, "TIME", strlen("TIME"),
        MSG_CONFIRM, (const struct sockaddr *)&servaddr,
            sizeof(servaddr));
    printf("Time request sent.\n");

    // Receive time from server
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, NULL, NULL);
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