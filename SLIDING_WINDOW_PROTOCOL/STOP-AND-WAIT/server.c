#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_DATA_SIZE 1024

typedef struct {
    char data[MAX_DATA_SIZE];
} Packet;

typedef struct {
    int frame_kind; // ACK:0, SEQ:1, FIN:2
    int sq_no;
    int ack;
    Packet packet;
} Frame;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size = sizeof(clientAddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Binding failed");
        exit(1);
    }

    Frame frame_recv;
    int frame_id = 0;

    while (1) {
        recvfrom(sockfd, &frame_recv, sizeof(Frame), 0, (struct sockaddr *)&clientAddr, &addr_size);
        
        if (frame_recv.frame_kind == 1 && frame_recv.sq_no == frame_id) {
            printf("[+] Frame Received: %s\n", frame_recv.packet.data);
            Frame ack_frame;
            ack_frame.sq_no = 0;
            ack_frame.frame_kind = 0;
            ack_frame.ack = frame_recv.sq_no + 1;
            sendto(sockfd, &ack_frame, sizeof(Frame), 0, (struct sockaddr *)&clientAddr, addr_size);
            printf("[+] Ack Sent\n");
            frame_id++;
        } else {
            printf("[-] Frame Not Received\n");
        }
    }

    close(sockfd);
    return 0;
}
    