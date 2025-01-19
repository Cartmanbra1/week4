#include <iostream>      // For input/output operations
#include <sys/socket.h>  // For socket functions and structures
#include <stdio.h>       // For perror to display error messages
#include <netinet/in.h>  // For sockaddr_in structure
#include <arpa/inet.h>   // For address conversion functions
#include <unistd.h>      // For close() to close the socket
#include <string.h>      // For string manipulation functions like memset and strlen

using namespace std;

int main() {

    // Define the server's IP address and port
    const char* ip_address = "127.0.0.1"; // Localhost IP
    const int port_no = 5555;            // Port to connect to

    // Create a TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket"); // Print error message if socket creation fails
    }

    // Configure the server's address structure
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));         // Clear the structure
    sin.sin_family = AF_INET;            // Use IPv4 addressing
    sin.sin_addr.s_addr = inet_addr(ip_address); // Set the server's IP address
    sin.sin_port = htons(port_no);       // Convert port number to network byte order

    // Attempt to connect to the server
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server"); // Print error message if connection fails
    }

    // Define the message to send to the server
    char data_addr[] = "Im a message";        // Message content
    int data_len = strlen(data_addr);         // Length of the message

    // Send the message to the server
    int sent_bytes = send(sock, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("error sending data"); // Print error message if sending fails
    }

    // Buffer to store the server's response
    char buffer[4096];
    int expected_data_len = sizeof(buffer); // Maximum size of the buffer

    // Receive data from the server
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        // Connection is closed
        cout << "Connection closed by the server." << endl;
    }
    else if (read_bytes < 0) {
        // Error while receiving data
        perror("error receiving data");
    }
    else {
        // Successfully received data
        cout << "Server response: " << buffer << endl;
    }

    // Close the socket
    close(sock);

    return 0; // Program ends successfully
}