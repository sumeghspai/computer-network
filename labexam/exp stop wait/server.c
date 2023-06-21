#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define SERVER_PORT 8888

int main() {
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen;
    char buffer[BUFFER_SIZE];

    // Create socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
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

    printf("Receiver: Waiting for messages...\n");

    while (1) {
        // Receive message from the sender
        memset(buffer, 0, sizeof(buffer));
        clientAddrLen = sizeof(clientAddr);
        if (recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen) < 0) {
            perror("Failed to receive message");
            exit(1);
        }

        printf("Receiver: Received message: %s", buffer);

        // Send ACK to the sender
        if (sendto(serverSocket, "ACK", strlen("ACK"), 0, (struct sockaddr*)&clientAddr, clientAddrLen) < 0) {
            perror("Failed to send ACK");
            exit(1);
        }
    }

    // Close the socket
    close(serverSocket);

    return 0;
}
