/**
 * Server skeleton code
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    // =================================================================
    // QUESTION 2: Socket Creation and Setup
    // =================================================================

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        error("Socket creation failed");
    }
    
    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);


    // TODO: Bind to a port...

    // TODO: Start listening at the port...


    printf("Server waiting for connections...\n");
    

    // TODO: Accept incoming client connection. This blocks until a client connects..

    
    printf("Client connected!\n");


    // =================================================================
    // QUESTION 3 & 4: Communication Loop (Connection open until client sends "quit")
    // - Send message from server to client, and vice versa (bidirectional communication)
    // -----------------------------------------------------------------
    // TODO:
    // Establish your own way of sending & receving messages (aka your own protocol). 
    // It can be as simple as sending plain text, and you're allowed to change anything from here onwards.
    // Remember to follow the expected flow that has been laid out in the workshop questions.
    // Note that following the laid out structure would make the client and server communicate 
    // in a turn-based manner. Refer to the blue note at the bottom of the workshop page for more info.
    // =================================================================
    
    char buffer[BUFFER_SIZE];           // For receiving
    char server_message[BUFFER_SIZE];   // For sending
    ssize_t bytes_received, bytes_sent;
    int connection_active = 1;          // Flag to control the communication loop


    // Main communication loop - continues until client sends "quit"
    while (connection_active) {
        // =============================================================
        // SERVER SENDS MESSAGE TO CLIENT
        // =============================================================

        printf("Enter message to client: ");
        fflush(stdout);  // Ensure prompt is displayed immediately

        // .....
        // .....


        // =============================================================
        // SERVER RECEIVES MESSAGE FROM CLIENT
        // =============================================================
        
        printf("Waiting for message from client...\n");
        fflush(stdout);
        
        // .....
        // .....

    }

    
    printf("Closing connections....\n");

    // TODO: Remember to close....


    return 0;
}