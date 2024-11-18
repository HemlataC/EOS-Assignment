#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_IN "fifo_in"
#define FIFO_OUT "fifo_out"


int main() {
    int fd_in, fd_out;
    int num1, num2, sum;

 mkfifo(FIFO_IN, 0666);
 mkfifo(FIFO_OUT, 0666);

fd_in = open(FIFO_IN, O_RDONLY);
    if (fd_in == -1) {
        perror("Error opening FIFO for reading");
        exit(1);
    }

    // Read two numbers from the client
    read(fd_in, &num1, sizeof(num1));
    read(fd_in, &num2, sizeof(num2));

    // Calculate the sum
    sum = num1 + num2;
    printf("Server: Received %d and %d. Calculated sum: %d\n", num1, num2, sum);

    // Open the FIFO for writing (client will read from here)
    fd_out = open(FIFO_OUT, O_WRONLY);
    if (fd_out == -1) {
        perror("Error opening FIFO for writing");
        exit(1);
    }

    // Send the result back to the client
    write(fd_out, &sum, sizeof(sum));

    // Close the FIFOs
    close(fd_in);
    close(fd_out);

    return 0;
}

