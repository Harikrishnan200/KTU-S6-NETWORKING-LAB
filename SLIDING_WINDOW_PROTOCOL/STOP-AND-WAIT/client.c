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
 
    int port = atoi(argv[1]);  // convert a string representation of an integer 
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[MAX_DATA_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&serverAddr, '\0', sizeof(serverAddr));  //\0' has a value of 0
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int frame_id = 0;
    Frame frame_send;
    Frame frame_recv;

    while (1) {
        frame_send.sq_no = frame_id;
        frame_send.frame_kind = 1;
        frame_send.ack = 0;

        printf("Enter Data: ");
        fgets(buffer, MAX_DATA_SIZE, stdin);  //stdin: Standard input stream. This stream is typically used for reading input from the user, such as keyboard input.
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character    // In other words, it finds the index of the first occurrence of '\n' in buffer
        strcpy(frame_send.packet.data, buffer);

        sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        printf("[+] Frame Sent\n");

        recvfrom(sockfd, &frame_recv, sizeof(Frame), 0, NULL, NULL);

        if (frame_recv.sq_no == 0 && frame_recv.ack == frame_id + 1) {
            printf("[+] Ack Received\n");
            frame_id++;
        } else {
            printf("[-] Ack Not Received\n");
        }
    }

    close(sockfd);
    return 0;
}
