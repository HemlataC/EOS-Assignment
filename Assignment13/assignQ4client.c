#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080       // Server port
#define SERVER_IP "127.0.0.1"  // Server IP address (localhost)

int main() {
    int sock;
    struct sockaddr_in server_addr;
    int num1, num2, sum;

    // Create the socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or Address not supported");
        close(sock);
        exit(1);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sock);
        exit(1);
    }

    // Input two numbers from the user
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    // Send the numbers to the server
    write(sock, &num1, sizeof(num1));
    write(sock, &num2, sizeof(num2));

    // Receive the result (sum) from the server
    read(sock, &sum, sizeof(sum));

    // Output the result
    printf("Client: Received sum from server: %d\n", sum);

    // Close the socket
    close(sock);

    return 0;
}

