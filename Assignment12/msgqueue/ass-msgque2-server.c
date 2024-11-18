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

    // Create or open the message queue
    mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
    if (mqid < 0) {
        perror("msgget() failed");
        _exit(1);
    }

    // Receive the message from the client
    ret = msgrcv(mqid, &m1, sizeof(m1) - sizeof(long), 101, 0);
    if (ret < 0) {
        perror("msgrcv() failed");
        _exit(1);
    }

    printf("Server: Received data - FIFO path: %s, File name: %s\n", m1.data1, m1.data2);

    // Open the FIFO path (m1.data1) for writing
    int fd = open(m1.data1, O_WRONLY);
    if (fd < 0) {
        perror("open() failed");
        _exit(1);
    }

    // Write a response to the FIFO
    ret = write(fd, m1.data2, strlen(m1.data2) + 1);
    if (ret < 0) {
        perror("write() failed");
        _exit(1);
    }
    printf("Server: Message sent to FIFO: %s\n", m1.data2);
    close(fd);

    return 0;
}

