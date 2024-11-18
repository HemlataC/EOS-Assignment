#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080       // Server port
#define MAX_CONN 5      // Maximum number of client connections

int main() {
    int server_fd, new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    int num1, num2, sum;

    // Create the socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections on any IP address
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the IP address and port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(1);
    }

    // Listen for incoming client connections
    if (listen(server_fd, MAX_CONN) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(1);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept a client connection
    addr_size = sizeof(client_addr);
    new_sock = accept(server_fd, (struct sockaddr *)&client_addr, &addr_size);
    if (new_sock == -1) {
        perror("Accept failed");
        close(server_fd);
        exit(1);
    }

    // Receive the two numbers from the client
    read(new_sock, &num1, sizeof(num1));
    read(new_sock, &num2, sizeof(num2));

    // Calculate the sum
    sum = num1 + num2;

    // Send the sum back to the client
    write(new_sock, &sum, sizeof(sum));

    printf("Server: Received %d and %d, Sum is: %d\n", num1, num2, sum);

    // Close the sockets
    close(new_sock);
    close(server_fd);

    return 0;
}

