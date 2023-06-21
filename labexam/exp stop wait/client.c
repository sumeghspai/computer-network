#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define SERVER_PORT 8888
#define SERVER_IP "127.0.0.1"

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
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

    printf("Sender: Enter message to send (type 'exit' to quit):\n");

    while (1) {
        // Read input from the user
        fgets(buffer, BUFFER_SIZE, stdin);

        // Check if the user wants to exit
        if (strcmp(buffer, "exit\n") == 0)
            break;

        // Send the message to the receiver
        if (sendto(clientSocket, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            perror("Failed to send message");
            exit(1);
        }

        // Receive ACK from the receiver
        memset(buffer, 0, sizeof(buffer));
        if (recvfrom(clientSocket, buffer, sizeof(buffer), 0, NULL, NULL) < 0) {
            perror("Failed to receive ACK");
            exit(1);
        }

        printf("Sender: Received ACK: %s\n", buffer);
    }

    // Close the socket
    close(clientSocket);

    return 0;
}
