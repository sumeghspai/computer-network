#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define SERVER_PORT 25
#define SERVER_IP "127.0.0.1"

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    // Set server details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddr.sin_addr)) <= 0) {
        perror("Invalid server IP address");
        exit(1);
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Failed to connect to the server");
        exit(1);
    }

    printf("Connected to SMTP Server\n");

    // Receive server response
    memset(buffer, 0, sizeof(buffer));
    // if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
    //     perror("Failed to receive server response");
    //     exit(1);
    // }
    // printf("Server: %s", buffer);

    // Send client command
    sprintf(buffer, "EHLO client.example.com\r\n");
    if (send(clientSocket, buffer, strlen(buffer), 0) < 0) {
        perror("Failed to send client command");
        exit(1);
    }

    // Receive server response
    memset(buffer, 0, sizeof(buffer));
    if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
        perror("Failed to receive server response");
        exit(1);
    }
    printf("Server: %s", buffer);

    // Send more client commands based on the SMTP protocol specifications

    // Close the socket
    close(clientSocket);

    return 0;
}
