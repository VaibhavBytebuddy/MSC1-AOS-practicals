#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t child_pid = 0;

// Signal handler for SIGCHLD (child termination)
void handle_sigchld(int sig) {
    int status;
    waitpid(child_pid, &status, 0);
    if (WIFEXITED(status)) {
        printf("Child exited with status: %d\n", WEXITSTATUS(status));
    } else {
        printf("Child terminated abnormally.\n");
    }
    exit(0);
}

// Signal handler for SIGALRM (timeout)
void handle_sigalrm(int sig) {
    printf("Child did not finish in time. Terminating child...\n");
    kill(child_pid, SIGKILL);
}

int main() {
    signal(SIGCHLD, handle_sigchld);
    signal(SIGALRM, handle_sigalrm);

    if ((child_pid = fork()) == 0) {
        // Child process: Replace with command (e.g., `sleep 10`)
        execlp("sleep", "sleep", "10", NULL);
        perror("execlp failed");
        exit(1);
    } else if (child_pid > 0) {
        // Parent process: Set a 5-second alarm
        alarm(5);
        pause();  // Wait for signals
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}
