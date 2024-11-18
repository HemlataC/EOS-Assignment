#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void run_command(const char *command) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: Execute the command
        int status = system(command);
        exit(WEXITSTATUS(status));  // Return exit status of the command
    }
    // Parent process: Just return and wait later
}

int main() {
    // Commands for compiling the source files
    const char *commands[] = {
        "gcc -c circle.c",
        "gcc -c square.c",
        "gcc -c rectangle.c",
        "gcc -c main.c"
    };
    
    pid_t pids[4];  // To store the PIDs of child processes
    
    // Step 1: Create child processes for compiling each source file
    for (int i = 0; i < 4; i++) {
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process: Execute the command
            int status = system(commands[i]);
            exit(WEXITSTATUS(status));  // Return exit status of the command
        } else {
            pids[i] = pid;
        }
    }

    // Step 2: Wait for all compilation children to finish
    for (int i = 0; i < 4; i++) {
        int status;
        waitpid(pids[i], &status, 0);
        
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) != 0) {
                printf("Child %d failed with exit status %d\n", pids[i], WEXITSTATUS(status));
                exit(1);  // Exit if any compilation fails
            }
        } else {
            printf("Child %d did not terminate normally\n", pids[i]);
            exit(1);
        }
    }

    // Step 3: Link the object files into the final executable
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: Execute the linking command
        int status = system("gcc -o program.out circle.o square.o rectangle.o main.o");
        exit(WEXITSTATUS(status));  // Return exit status of the command
    } else {
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) != 0) {
                printf("Linking failed with exit status %d\n", WEXITSTATUS(status));
                exit(1);
            }
        } else {
            printf("Linking process did not terminate normally\n");
            exit(1);
        }
    }

    // Step 4: Run the final executable if linking succeeded
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: Execute the program
        int status = system("./program.out");
        exit(WEXITSTATUS(status));  // Return exit status of the command
    } else {
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Program exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Program did not terminate normally\n");
            exit(1);
        }
    }

    return 0;
}

