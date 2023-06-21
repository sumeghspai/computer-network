#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_SIZE 4
#define TIMEOUT_DURATION 3

typedef struct {
    int seqNum;
    bool ackReceived;
    char data[1024];
} Packet;

void sendPacket(Packet packet) {
    // Simulate sending packet over the network
    printf("Sending packet with sequence number %d\n", packet.seqNum);
    // ...
    // Send the packet
}

void receiveAck(Packet ack) {
    // Process received ACK packet
    printf("Received ACK for sequence number %d\n", ack.seqNum);
    // ...
    // Process the ACK
}

int main() {
    srand(time(NULL));
    
    // Simulated network delay and loss
    double lossProbability = 0.1;  // 10% packet loss probability
    
    Packet window[WINDOW_SIZE];
    int base = 0;
    int nextSeqNum = 0;
    
    while (true) {
        // Send packets within the window
        while (nextSeqNum < base + WINDOW_SIZE) {
            Packet packet;
            packet.seqNum = nextSeqNum;
            packet.ackReceived = false;
            sprintf(packet.data, "Packet %d", nextSeqNum);
            
            sendPacket(packet);
            
            // Place the sent packet into the window
            window[nextSeqNum % WINDOW_SIZE] = packet;
            
            nextSeqNum++;
        }
        
        // Receive ACKs
        while (true) {
            Packet ack;
            // Simulate network delay and loss
            double randValue = (double)rand() / RAND_MAX;
            if (randValue < lossProbability) {
                // Packet loss, skip receiving ACK
                printf("ACK for sequence number %d is lost\n", window[base % WINDOW_SIZE].seqNum);
                break;
            }
            
            // Simulate receiving ACK packet
            ack.seqNum = window[base % WINDOW_SIZE].seqNum;
            ack.ackReceived = true;
            receiveAck(ack);
            
            // Update the base index and shift the window
            base++;
            
            // Stop receiving ACKs if the window is empty
            if (base == nextSeqNum)
                break;
        }
    }
    
    return 0;
}
