#include <iostream>      // For input/output operations
#include <sys/socket.h>  // For socket programming functions
#include <stdio.h>       // For perror to display error messages
#include <netinet/in.h>  // For sockaddr_in structure
#include <arpa/inet.h>   // For inet_addr to convert IP addresses
#include <unistd.h>      // For close() to close sockets
#include <string.h>      // For memset to initialize structures

using namespace std;

int main() {

    // Define the server's IP address and port number
    const char* ip_address = "127.0.0.1"; // Server IP (localhost)
    const int port_no = 5555;            // Server port number

    // Create a UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket"); // Display error if socket creation fails
    }

    // Configure the server address structure
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));              // Clear the structure
    sin.sin_family = AF_INET;                 // Use IPv4 addressing
    sin.sin_addr.s_addr = inet_addr(ip_address); // Set server IP
    sin.sin_port = htons(port_no);            // Convert port to network byte order

    // Define the message to send
    char data[] = "hello";
    int data_len = sizeof(data);

    // Send the message to the server
    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket"); // Display error if message sending fails
    }

    // Prepare to receive a response from the server
    struct sockaddr_in from;               // Structure to hold sender's address
    unsigned int from_len = sizeof(from);  // Size of the sender's address structure
    char buffer[4096];                     // Buffer to store received data

    // Receive the response from the server
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket"); // Display error if message receiving fails
    }

    // Display the response from the server
    cout << "The server sent: " << buffer << endl;

    // Close the socket
    close(sock);

    return 0; // Program ends successfully
}
