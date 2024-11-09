#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Error in fork
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is running...\n", getpid());
        // Exit with a specific status, e.g., 5
        exit(5);
    } else {
        // Parent process
        int status;
        pid_t child_pid = wait(&status);  // Wait for the child process to terminate

        if (child_pid == -1) {
            perror("wait failed");
            exit(1);
        }

        printf("Child process (PID: %d) terminated. ", child_pid);

        // Check if the child exited normally
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Exit status: %d\n", exit_status);
        } else {
            printf("Child did not exit normally.\n");
        }
    }

    return 0;
}
