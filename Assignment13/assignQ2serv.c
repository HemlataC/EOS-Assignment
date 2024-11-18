#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MSG_KEY 1234          // Message Queue Key
#define MAX_FILE_NAME 256     // Max length of file name

// Structure for message queue
struct msgbuf {
    long mtype;
    char fifo_name[MAX_FILE_NAME];
    char file_name[MAX_FILE_NAME];
};

void send_file(const char *fifo_name, const char *file_name) {
    int fifo_fd, file_fd;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    // Open the FIFO for writing
    fifo_fd = open(fifo_name, O_WRONLY);
    if (fifo_fd == -1) {
        perror("Error opening FIFO for writing");
        exit(1);
    }

    // Open the file to send
    file_fd = open(file_name, O_RDONLY);
    if (file_fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    // Read file and send it through the FIFO
    while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(fifo_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to FIFO");
            exit(1);
        }
    }

    printf("Server: File sent successfully via FIFO.\n");

    // Close the files
    close(file_fd);
    close(fifo_fd);
}

int main() {
    int msgid;
    struct msgbuf msg;

    // Create message queue
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Error creating message queue");
        exit(1);
    }

    // Receive the message from the client
    if (msgrcv(msgid, &msg, sizeof(msg), 1, 0) == -1) {
        perror("Error receiving message");
        exit(1);
    }

    printf("Server: Received FIFO name: %s and file name: %s\n", msg.fifo_name, msg.file_name);

    // Create the FIFO for sending the file
    if (mkfifo(msg.fifo_name, 0600) == -1) {
        perror("Error creating FIFO");
        exit(1);
    }

    // Send the file through the FIFO
    send_file(msg.fifo_name, msg.file_name);

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

