#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define MQ_KEY  0x1234

typedef struct msg {
    long id;
    char data[32];
}msg_t;

int main() {
    int mqid, pid, s, ret;
    // create a message queue
    mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
    if(mqid < 0) {
        perror("msgget() failed");
        _exit(1);
    }

    // create child process
    pid = fork();
    if(pid == 0) {
        // child send message to parent - msgsnd()
        msg_t m1;
        m1.id = 101;
        printf("child: enter a message: ");
        gets(m1.data);
        ret = msgsnd(mqid, &m1, sizeof(msg_t)-sizeof(long), 0);
        if(ret < 0)
            perror("child: msgsnd() failed");
        else
            printf("child: message sent: %s\n", m1.data);
    }
    else {
        // parent receive message from child - msgrcv()
        msg_t m2;
        printf("parent: waiting for child message...\n");
        ret = msgrcv(mqid, &m2, sizeof(msg_t)-sizeof(long), 101, 0);
        if(ret < 0)
            perror("msgrcv() failed");
        else
            printf("parent: received: %s\n", m2.data);
        // parent cleanup child (no zombie)
        waitpid(pid, &s, 0);
        // parent destroys message queue
        //msgctl(mqid, IPC_RMID, NULL);
    }
    return 0;
}
