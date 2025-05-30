/**
 * Client skeleton code
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"  // localhost
#define BUFFER_SIZE 1024

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main() {
    int client_fd;
    struct sockaddr_in server_addr;

    // =================================================================
    // QUESTION 2: Socket Creation and Setup
    // =================================================================
    
    // Create socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    
    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // TODO: Connect to ....?
    
    printf("Connected to server!\n");
    
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


    char buffer[BUFFER_SIZE];
    char client_message[BUFFER_SIZE];
    ssize_t bytes_received, bytes_sent;
    int connection_active = 1; // Flag to control

    // Main communication loop - continues until client sends "quit"
    while (connection_active) {
        
        // =============================================================
        // CLIENT RECEIVES MESSAGE FROM SERVER
        // =============================================================

        printf("Waiting for message from server...\n");
        fflush(stdout);  // Ensure prompt is displayed immediately
        
        // .....
        // .....

        
        // =============================================================
        // CLIENT SENDS MESSAGE TO SERVER
        // =============================================================
        
        printf("Enter message to send to server (or 'quit' to exit): ");
        fflush(stdout);
        
        // .....
        // .....
        
    }

    printf("Closing connection....\n");
    
    // TODO: Remember to close....


    return 0;
}