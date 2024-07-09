#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;                  
    struct sockaddr_in server_address, client_address;  //server_socket and client_socket are declared to store the server and client socket file descriptors respectively. 
    socklen_t client_address_len = sizeof(client_address); //client_address_len stores the size of the client address structure. ,socklen_t is a data type used in socket programming in C. It stands for "socket length type". It's used to represent the length of socket addresses. 
    char buffer[BUFFER_SIZE] = {0};
    char *message = "Hello from server";

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("Socket creation error");
        exit(0);
    }  

    // Set server address     (Here, the server address structure server_address is initialized)
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;  // INADDR_ANY means the server will accept connections on any of the host's network addresses
    server_address.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {     // bind() is used to binds the socket to the server address
        printf("Bind failed");
        exit(0);
    }

    // Listen for connections
    if (listen(server_socket, 3) < 0) {   //This line puts the server socket in the listening state using the listen() function. It specifies the maximum number of queued connections that the system should allow (in this case, 3)
        printf("Listen failed");
        exit(0);
    }

    // Accept incoming connection
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len)) < 0) {
        printf("Accept failed");
        exit(0);
    }

    // Receive data from client
    read(client_socket, buffer, BUFFER_SIZE);    // or recv(client_socket, buffer, BUFFER_SIZE, 0);   0 -> FLAG BIT
    printf("Message from client: %s\n", buffer);

    // Send data to client
    write(client_socket, message, strlen(message));  // or send(client_socket, message, strlen(message), 0);   0 -> FLAG BIT
    printf("Message sent to client\n");

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}

//OUTPUT
// Message from client: Hello from client
// Message sent to client