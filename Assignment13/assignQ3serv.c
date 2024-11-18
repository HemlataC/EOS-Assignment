#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/sum_socket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr;
    int num1, num2, sum;

    // Create the Unix domain socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Prepare the sockaddr_un structure
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Bind the socket to the specified path
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("Bind failed");
        exit(1);
    }

    // Listen for incoming client connections
    if (listen(server_fd, 5) == -1) {
        perror("Listen failed");
        exit(1);
    }

    printf("Server is waiting for a client connection...\n");

    // Accept the client connection
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1) {
        perror("Accept failed");
        exit(1);
    }

    // Read two numbers sent by the client
    if (read(client_fd, &num1, sizeof(num1)) == -1) {
        perror("Read failed");
        exit(1);
    }
    if (read(client_fd, &num2, sizeof(num2)) == -1) {
        perror("Read failed");
        exit(1);
    }

    // Calculate the sum
    sum = num1 + num2;

    // Send the result (sum) back to the client
    if (write(client_fd, &sum, sizeof(sum)) == -1) {
        perror("Write failed");
        exit(1);
    }

    // Close the client and server sockets
    close(client_fd);
    close(server_fd);

    // Remove the socket file
    unlink(SOCKET_PATH);

    return 0;
}

