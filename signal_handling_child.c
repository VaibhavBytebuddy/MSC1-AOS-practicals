#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sighup(int sig) {
    printf("Child received SIGHUP\n");
}

void handle_sigint(int sig) {
    printf("Child received SIGINT\n");
}

void handle_sigquit(int sig) {
    printf("My DADDY has killed me!!!\n");
    exit(0);
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        // Set up signal handlers
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        // Child process waits indefinitely for signals
        while (1) {
            pause();  // Wait for signals
        }
    } else if (pid > 0) {  // Parent process
        for (int i = 0; i < 10; i++) {
            // Alternate sending SIGHUP and SIGINT every 3 seconds
            sleep(3);
            if (i % 2 == 0) {
                kill(pid, SIGHUP);
            } else {
                kill(pid, SIGINT);
            }
        }
        // After 30 seconds, send SIGQUIT to terminate the child
        kill(pid, SIGQUIT);
        wait(NULL);  // Wait for child to exit
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}
