#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

// Go Back N Client implementation in C. Run server first

#define SERVER_PORT 6000
#define CLIENT_PORT 8000
#define DATA 0
#define ACK 1
#define FIN 2

typedef struct Frame {
    char data;
    int type;
    int no;
} Frame;

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(-1);
    }
    printf("Socket successfully created..\n");

    struct sockaddr_in cliaddr, servaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(CLIENT_PORT);
    cliaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) != 0) {
        printf("Socket bind failed...\n");
        exit(-1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // Client side processing...
    unsigned int len = sizeof(servaddr);
    Frame f;
    while (1) {
        if (recvfrom(sockfd, &f, sizeof(f), 0, (struct sockaddr *)&servaddr, &len) > 0) {
            if (f.type == FIN) {
                printf("Received FIN. Transmission complete.\n");
                break;
            } else if (f.type == DATA) {
                printf("Received [%c] in frame [%d]. Sending ACK\n", f.data, f.no);
                Frame ack;
                ack.type = ACK;
                ack.no = f.no;
                sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&servaddr, len);
            }
        }
    }

    // Close the socket
    close(sockfd);
}
