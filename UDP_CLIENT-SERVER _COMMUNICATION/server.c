#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    char *message = "Hello from server";

    // Create UDP socket
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {  // 0 indicates default protocol
        printf("Socket creation failed");
        exit(0);
    }

    // Initialize server address struct
    //memset(&server_addr, 0, sizeof(server_addr));  //memset: This is a function provided by the C standard library. It stands for "memory set" and is commonly used to set a block of memory to a particular value.
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("Bind failed");
        exit(0);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        socklen_t client_addr_len = sizeof(client_addr);

        // Receive message from client
        int recv_len = recvfrom(server_socket, buffer, BUFFER_SIZE, 0,
                                (struct sockaddr *)&client_addr, &client_addr_len);  //recvfrom() call, 0 is used to indicate that none of these flags are being passed
        if (recv_len == -1) {
            printf("Receive failed");
            exit(0);
        }

        // Print received message
        buffer[recv_len] = '\0';
        printf("Received message from client: %s\n", buffer);

        // Echo message back to client
        if (sendto(server_socket, message, strlen(message), 0,
                   (struct sockaddr *)&client_addr, client_addr_len) == -1) {
            printf("Sendto failed");
            exit(0);
        }
    }

    // Close socket
    close(server_socket);

    return 0;
}

 /* 
In the case of UDP socket programming, the loop described in the 
provided code is used to handle multiple client communications concurrently, 
rather than sequentially accepting connections from multiple clients as you might see in TCP socket programming.
With UDP, each client communicates with the server by sending individual datagrams (packets), 
and the server can handle these datagrams independently. The server does not establish a persistent connection with 
each client as in TCP; instead, it simply listens for incoming datagrams and responds to them.
   */


  /*n the recvfrom() function call, client_addr_len represents the size of the client_addr structure that is passed as an argument.

The recvfrom() function is used to receive messages from a socket. 
When using UDP sockets, it's common to receive messages from different clients. To identify the sender of the received message, 
recvfrom() expects a pointer to a socket address structure (struct sockaddr) where it can store the sender's address.
 Additionally, it also requires the size of this address structure.*/


 /* 
 output
 
 Server is listening on port 12345...
Received message from client: Hello from client!

*/