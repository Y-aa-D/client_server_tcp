#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char message[BUFFER_SIZE];
    ssize_t message_length;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Prepare the sockaddr_in structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_ADDRESS, &(server_address.sin_addr)) <= 0) {
        perror("invalid address or address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    while (1) {
        printf("Enter message: ");
        fgets(message, BUFFER_SIZE, stdin);

        // Send message to server
        message_length = send(client_socket, message, strlen(message), 0);
        if (message_length < 0) {
            perror("send failed");
            exit(EXIT_FAILURE);
        }

        // Receive response from server
        message_length = recv(client_socket, message, BUFFER_SIZE, 0);
        if (message_length < 0) {
            perror("recv failed");
            exit(EXIT_FAILURE);
        }

        printf("Server response: %.*s", (int)message_length, message);

        if (strcmp(message, "disconnect\n") == 0) {
            printf("Disconnected from server\n");
            break;
        }

        memset(message, 0, BUFFER_SIZE);
    }

    close(client_socket);

    return 0;
}
