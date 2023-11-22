#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int child_pid;
int table_index;
void parentSignalHandler(int sig) {
    if (sig == SIGINT) {
        printf("Received SIGINT signal in parent process\n");
        kill(child_pid, SIGINT); // Forward SIGINT to child process
    }
}

void childSignalHandler(int sig) {
    if (sig == SIGINT) {
        if (table_index < 9) {
            printf("Cannot terminate, multiplication table is still running\n");
        } else {
            printf("Termination received. Killing both parent and child processes\n");
            kill(getppid(), SIGKILL); // Send SIGKILL to parent process
            kill(getpid(), SIGKILL); // Send SIGKILL to self
        }
    }
}

int main() {
    int child_pid, table_index;

    // Create a child process using fork()
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(1);
    } else if (child_pid == 0) { // Child process
        signal(SIGINT, childSignalHandler); // Set signal handler for SIGINT

        // Print multiplication tables up to 20
        for (table_index = 1; table_index <= 20; table_index++) {
            printf("Multiplication table of %d:\n", table_index);
            for (int j = 1; j <= 10; j++) {
                printf("%d x %d = %d\n", table_index, j, table_index * j);
            }
            sleep(1); // Delay for 1 second
        }

        exit(0);
    } else { // Parent process
        signal(SIGINT, parentSignalHandler); // Set signal handler for SIGINT

        while (1) {
            printf("Parent process is sleeping...\n");
            sleep(5); // Sleep for 5 seconds
        }
    }
    wait(NULL); // Wait for child process to finish
    printf("Child process finished.\n");
    return 0;
}
