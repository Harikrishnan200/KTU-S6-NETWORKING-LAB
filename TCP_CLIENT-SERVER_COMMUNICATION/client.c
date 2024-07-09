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
        printf("Socket creation error");           // 'perror()' prints an error message              
        exit(0);
    }

    // Set server address     (Here, the server address structure server_address is initialized)
    server_address.sin_family = AF_INET;   // AF_INET for IPv4
    server_address.sin_port = htons(PORT);  // port number is converted to network byte order using htons() function
    server_address.sin_addr.s_addr = INADDR_ANY;
    

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        printf("Connection failed");
        exit(0);
    }

    // Send data to server
    char *message = "Hello from client";
    write(client_socket, message, strlen(message));  // or send(client_socket, message, strlen(message), 0);
    printf("Message sent to server\n");

    // Receive data from server
    read(client_socket, buffer, BUFFER_SIZE);   // or recv(client_socket, buffer, BUFFER_SIZE, 0);
    printf("Message from server: %s\n", buffer);

    // Close socket
    close(client_socket);

 return 0;
}

//OUTPUT
// Message sent to server
// Message from server: Hello from server