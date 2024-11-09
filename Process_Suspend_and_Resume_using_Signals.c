#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// Signal handler for SIGCONT
void cont_handler(int signum) {
    printf("Process %d resumed\n", getpid());
}

int main() {
    pid_t pid;
    
    // Register SIGCONT handler
    if (signal(SIGCONT, cont_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    // Create child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {  // Child process
        printf("Child process (PID: %d) starting work...\n", getpid());
        
        // Simulate continuous work
        while(1) {
            printf("Child working... PID: %d\n", getpid());
            sleep(1);
        }
    } 
    else {  // Parent process
        printf("Parent process (PID: %d) controlling child (PID: %d)\n", 
               getpid(), pid);
        
        // Give child time to start
        sleep(3);
        
        // Suspend child
        printf("\nSuspending child process...\n");
        if (kill(pid, SIGSTOP) == -1) {
            perror("kill (SIGSTOP)");
            exit(1);
        }
        
        printf("Child process suspended. Waiting 3 seconds...\n");
        sleep(3);
        
        // Resume child
        printf("\nResuming child process...\n");
        if (kill(pid, SIGCONT) == -1) {
            perror("kill (SIGCONT)");
            exit(1);
        }
        
        sleep(3);
        
        // Terminate child
        printf("\nTerminating child process...\n");
        if (kill(pid, SIGTERM) == -1) {
            perror("kill (SIGTERM)");
            exit(1);
        }
        
        // Wait for child to terminate
        wait(NULL);
        printf("Child process terminated\n");
    }

    return 0;
}