#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

// Maximum number of clients the server can handle simultaneously
#define MAX_CLIENTS 5
// Buffer size for reading data from clients
#define BUFFER_SIZE 1024

// Function to handle communication with a single client
void *handle_client(void *socket_desc) {
    int sock = *(int *)socket_desc;
    char buffer[BUFFER_SIZE];
    int read_size;

    // Loop to continuously receive and send messages until the client disconnects
    while ((read_size = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        printf("Received: %s\n", buffer);
        send(sock, buffer, strlen(buffer), 0);
    }

    // Handle client disconnection or error
    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else {
        perror("recv failed");
    }

    // Close the socket after handling the client
    close(sock);
    return 0;
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    pthread_t thread_id[MAX_CLIENTS]; // Array to hold thread IDs

    // Create a socket for the server
    server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000); // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces

    // Bind the socket to the server address
    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Start listening for incoming connections
    listen(server_sock, MAX_CLIENTS);

    // Prepare to accept connections
    addr_size = sizeof(client_addr);

    // Main loop to accept and handle clients
    while (1) {
        // Accept a new connection
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);

        // Find an available thread ID to handle the client
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (thread_id[i] == 0) { // Check if the thread ID is not in use
                // Create a new thread to handle the client
                thread_id[i] = pthread_create(&thread_id[i], NULL, handle_client, &client_sock);
                if (thread_id[i] < 0) {
                    perror("Could not create thread");
                    return 1;
                }
                break; // Exit the loop once a thread is successfully created
            }
        }
    }

    return 0;
}


/*

gcc -o server server.c -lpthread
./server

*/