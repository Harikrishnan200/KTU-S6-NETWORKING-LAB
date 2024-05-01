#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    const char *message = "Hello, server!";

    // Create UDP socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    // Send message to server
    if (sendto(client_socket, message, strlen(message), 0,
               (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Sendto failed");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to server: %s\n", message);

    // Receive response from server
    socklen_t server_addr_len = sizeof(server_addr);
    int recv_len = recvfrom(client_socket, buffer, BUFFER_SIZE, 0,
                            (struct sockaddr *)&server_addr, &server_addr_len);
    if (recv_len == -1) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }

    // Print server's response
    buffer[recv_len] = '\0';
    printf("Received response from server: %s\n", buffer);

    // Close socket
    close(client_socket);

    return 0;
}
