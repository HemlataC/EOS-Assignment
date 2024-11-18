#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/sum_socket"

int main() {
    int client_fd;
    struct sockaddr_un server_addr;
    int num1, num2, sum;

    // Create the Unix domain socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Prepare the sockaddr_un structure
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("Connect failed");
        exit(1);
    }

    // Input two numbers from the user
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    // Send the numbers to the server
    if (write(client_fd, &num1, sizeof(num1)) == -1) {
        perror("Write failed");
        exit(1);
    }
    if (write(client_fd, &num2, sizeof(num2)) == -1) {
        perror("Write failed");
        exit(1);
    }

    // Read the result (sum) from the server
    if (read(client_fd, &sum, sizeof(sum)) == -1) {
        perror("Read failed");
        exit(1);
    }

    // Output the result
    printf("The sum of %d and %d is: %d\n", num1, num2, sum);

    // Close the socket
    close(client_fd);

    return 0;
}

