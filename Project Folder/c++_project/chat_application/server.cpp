// erver.cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <thread>  // For multi-threading
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>  // For close()

// Function to handle a client connection
void handleClient(int clientSocket) {
    // Placeholder code for handling a client
    char buffer[1024];
    ssize_t bytesRead;

    // Example: Echo back messages from the client
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        send(clientSocket, buffer, bytesRead, 0);
    }

    // Close the client socket
    close(clientSocket);
}

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket.\n";
        return -1;
    }

    // Set up the server address structure
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);  // Use any port you prefer

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding server socket.\n";
        close(serverSocket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening for connections.\n";
        close(serverSocket);
        return -1;
    }

    std::cout << "Server is listening on port 8080...\n";

    // Accept incoming connections and handle them in separate threads
    while (true) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);

        // Accept a new connection
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket == -1) {
            std::cerr << "Error accepting client connection.\n";
            continue;
        }

        // Start a new thread to handle the client
        std::thread(handleClient, clientSocket).detach();
    }

    // Close the server socket (this code is unreachable in this example)
    close(serverSocket);

    return 0;
}
S
