#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_socket;                    // to store the client socket file descriptor
    struct sockaddr_in server_address;   // "server_address" is declared to store the server address information
    char buffer[BUFFER_SIZE] = {0};     // 'buffer' is declared to store the data to be sent and received.

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");           // 'perror()' prints an error message              
        exit(EXIT_FAILURE);
    }

    // Set server address     (Here, the server address structure server_address is initialized)
    server_address.sin_family = AF_INET;   // AF_INET for IPv4
    server_address.sin_port = htons(PORT);  // port number is converted to network byte order using htons() function

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send data to server
    char *message = "Hello from client";
    send(client_socket, message, strlen(message), 0);
    printf("Message sent to server\n");

    // Receive data from server
    read(client_socket, buffer, BUFFER_SIZE);
    printf("Message from server: %s\n", buffer);

    // Close socket
    close(client_socket);

 return 0;
}