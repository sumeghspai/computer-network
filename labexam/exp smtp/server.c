#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define SERVER_PORT 25

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen;
    char buffer[BUFFER_SIZE];

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    // Set server details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the server address
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Failed to bind socket");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 1) < 0) {
        perror("Failed to listen for connections");
        exit(1);
    }

    printf("SMTP Server listening on port %d\n", SERVER_PORT);

    // Accept incoming connection
    clientAddrLen = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket < 0) {
        perror("Failed to accept connection");
        exit(1);
    }

    printf("Incoming connection accepted\n");

    // Receive client command
    memset(buffer, 0, sizeof(buffer));
    if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
        perror("Failed to receive client command");
        exit(1);
    }
    printf("Client: %s", buffer);

    // Send server response
    sprintf(buffer, "220 SMTP Server ready\r\n");
    if (send(clientSocket, buffer, strlen(buffer), 0) < 0) {
        perror("Failed to send server response");
        exit(1);
    }

    // Receive more client commands and handle them accordingly
    // Implement the SMTP server logic based on the SMTP protocol specifications

    // Close client socket
    close(clientSocket);

    // Close server socket
    close(serverSocket);

    return 0;
}
