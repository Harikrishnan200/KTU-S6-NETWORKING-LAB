#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char *message = "Hello from client!";

    // Create UDP socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        printf("Socket creation failed");
        exit(0);
    }

    // Initialize server address struct
    // memset(&server_addr, 0, sizeof(server_addr));  // memory initialization
    server_addr.sin_family = AF_INET;  // AF_INET is the protocol family of ipv4
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Send message to server
    if (sendto(client_socket, message, strlen(message), 0,
               (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("Sendto failed");
        exit(0);
    }

    printf("Message sent to server: %s\n", message);

    // Receive response from server
    socklen_t server_addr_len = sizeof(server_addr);
    int recv_len = recvfrom(client_socket, buffer, BUFFER_SIZE, 0,
                            (struct sockaddr *)&server_addr, &server_addr_len);
    if (recv_len == -1) {
        printf("Receive failed");
        exit(0);
    }

    // Print server's response
    buffer[recv_len] = '\0';
    printf("Received response from server: %s\n", buffer);

    // Close socket
    close(client_socket);

    return 0;
}


/*output

Message sent to server: Hello from client!
Received response from server: Hello from server

*/
