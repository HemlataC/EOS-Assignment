#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>
#include <fcntl.h>

#define MQ_KEY  0x1234

typedef struct msg {
    long id;       
    char data1[32]; 
    char data2[32];
} msg_t;

int main() {
    int mqid, ret;
    msg_t m1;

    // Initialize the message data
    m1.id = 101; // Unique message ID
    printf("Enter FIFO path: ");
    scanf("%s", m1.data1); // Get FIFO path from user
    printf("Enter file name: ");
    scanf("%s", m1.data2); // Get file name from user

    // Create or open the message queue
    mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
    if (mqid < 0) {
        perror("msgget() failed");
        _exit(1);
    }

    // Send the message
    ret = msgsnd(mqid, &m1, sizeof(msg_t) - sizeof(long), 0);
    if (ret < 0) {
        perror("msgsnd() failed");
        _exit(1);
    }
    printf("Data sent: %s and %s\n", m1.data1, m1.data2);

    // Open the input file (FIFO) for reading
    int fd = open(m1.data1, O_RDONLY);
    if (fd < 0) {
        perror("open() failed");
        _exit(1);
    }

    char buf2[32];
    printf("Client: waiting for message...\n");

    // Read data from the FIFO
    ret = read(fd, buf2, sizeof(buf2));
    if (ret < 0) {
        perror("read() failed");
        _exit(1);
    }
    printf("Client: Message received: %d bytes = %s\n", ret, buf2);
    close(fd);

    // Create and write data into the new file
    fd = open(m1.data2, O_TRUNC | O_WRONLY | O_CREAT, 0600);
    if (fd < 0) {
        perror("open() failed");
        _exit(1);
    }

    char buf[] = "Mauli Gnage";
    ret = write(fd, buf, strlen(buf) + 1); // write the string
    if (ret < 0) {
        perror("write() failed");
        _exit(1);
    }
    printf("Client: Data written to file\n");
    close(fd);

    // Read back the written file content
    fd = open(m1.data2, O_RDONLY);
    if (fd < 0) {
        perror("open() failed");
        _exit(1);
    }

    char buff[32];
    ret = read(fd, buff, sizeof(buff));
    if (ret < 0) {
        perror("read() failed");
        _exit(1);
    }

    printf("Client: File content: %s\n", buff);
    close(fd);

    return 0;
}
