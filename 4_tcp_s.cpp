#include <iostream>      // For input/output operations
#include <sys/socket.h>  // For socket-related functions and constants
#include <stdio.h>       // For perror to display error messages
#include <netinet/in.h>  // For sockaddr_in structure
#include <arpa/inet.h>   // For address-related functions
#include <unistd.h>      // For close() to close sockets
#include <string.h>      // For string manipulation functions like memset

using namespace std;

int main() {

    const int server_port = 5555; // Port number the server will listen on

    // Create a TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket"); // Print error if socket creation fails
    }

    // Configure the server's address structure
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));         // Clear the structure
    sin.sin_family = AF_INET;            // Use IPv4 addressing
    sin.sin_addr.s_addr = INADDR_ANY;    // Bind to all available network interfaces
    sin.sin_port = htons(server_port);   // Convert port number to network byte order

    // Bind the socket to the specified IP and port
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket"); // Print error if binding fails
    }

    // Start listening for incoming connections
    if (listen(sock, 5) < 0) { // Allow a backlog of up to 5 pending connections
        perror("error listening to a socket"); // Print error if listening fails
    }

    // Accept a connection from a client
    struct sockaddr_in client_sin;         // Structure to store client's address
    unsigned int addr_len = sizeof(client_sin); // Length of the client's address structure
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client"); // Print error if accepting fails
    }

    // Buffer to store data received from the client
    char buffer[4096];                          // Maximum size of the buffer
    int expected_data_len = sizeof(buffer);     // Expected size of data
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0); // Receive data

    // Handle the data received
    if (read_bytes == 0) {
        // Connection is closed
        cout << "Client closed the connection." << endl;
    }
    else if (read_bytes < 0) {
        // Error occurred while receiving
        perror("error receiving data from client");
    }
    else {
        // Successfully received data
        cout << "Received from client: " << buffer << endl;
    }

    // Send the received data back to the client (echo)
    int sent_bytes = send(client_sock, buffer, read_bytes, 0); // Send back the same data
    if (sent_bytes < 0) {
        perror("error sending to client"); // Print error if sending fails
    }

    // Close the client socket
    close(client_sock);

    // Close the server socket
    close(sock);

    return 0; // Program ends successfully
}
