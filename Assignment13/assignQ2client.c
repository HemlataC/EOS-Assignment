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

void receive_file(const char *fifo_name, const char *file_name) {
    int fifo_fd, file_fd;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    // Open the FIFO for reading
    fifo_fd = open(fifo_name, O_RDONLY);
    if (fifo_fd == -1) {
        perror("Error opening FIFO for reading");
        exit(1);
    }

    // Open the file to save the received content
    file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file_fd == -1) {
        perror("Error opening file to write");
        exit(1);
    }

    // Read from FIFO and write to the file
    while ((bytes_read = read(fifo_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(file_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to file");
            exit(1);
        }
    }

    printf("Client: File received and saved as %s\n", file_name);

    // Close the files
    close(file_fd);
    close(fifo_fd);
}

int main() {
    int msgid;
    struct msgbuf msg;

    // Get FIFO name and file name from user
    char fifo_name[MAX_FILE_NAME], file_name[MAX_FILE_NAME];

    printf("Enter FIFO name for communication: ");
    scanf("%s", fifo_name);

    printf("Enter file name to send: ");
    scanf("%s", file_name);

    // Create message queue
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Error creating message queue");
        exit(1);
    }

    // Prepare the message to send to the server
    msg.mtype = 1; // Set message type
    strncpy(msg.fifo_name, fifo_name, sizeof(msg.fifo_name));
    strncpy(msg.file_name, file_name, sizeof(msg.file_name));

    // Send the message to the server
    if (msgsnd(msgid, &msg, sizeof(msg), 0) == -1) {
        perror("Error sending message");
        exit(1);
    }

    // Receive the file through the FIFO
    receive_file(fifo_name, file_name);

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}

