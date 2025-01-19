#include <iostream>      // For input/output operations
#include <sys/socket.h>  // For socket programming functions
#include <stdio.h>       // For perror to display error messages
#include <netinet/in.h>  // For sockaddr_in structure
#include <arpa/inet.h>   // For address manipulation functions
#include <unistd.h>      // For close() to close sockets
#include <string.h>      // For memset to initialize structures

using namespace std;

int main() {

    // Define the server's port number
    const int server_port = 5555; // The port on which the server will listen

    // Create a UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket"); // Display error if socket creation fails
    }

    // Configure the server address structure
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));      // Clear the structure
    sin.sin_family = AF_INET;         // Use IPv4 addressing
    sin.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
    sin.sin_port = htons(server_port); // Convert port to network byte order

    // Bind the socket to the specified IP and port
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to socket"); // Display error if binding fails
    }

    // Prepare to receive data from the client
    struct sockaddr_in from;               // Structure to store the client's address
    unsigned int from_len = sizeof(from);  // Size of the client's address structure
    char buffer[4096];                     // Buffer to store received data

    // Receive data from the client
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket"); // Display error if receiving fails
    }

    // Display the data received from the client
    cout << "The client sent: " << buffer << endl;

    // Send the received data back to the client (echo)
    int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from));
    if (sent_bytes < 0) {
        perror("error writing to socket"); // Display error if sending fails
    }

    // Close the socket
    close(sock);

    return 0; // Program ends successfully
}