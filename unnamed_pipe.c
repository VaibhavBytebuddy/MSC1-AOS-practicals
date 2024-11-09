#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int pipe_fd[2];  // Pipe file descriptors
    pid_t pid;
    char buffer[100];

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Create a child process
    pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Write messages to the pipe
        write(pipe_fd[1], "Hello World\n", strlen("Hello World\n"));
        write(pipe_fd[1], "Hello SPPU\n", strlen("Hello SPPU\n"));
        write(pipe_fd[1], "Linux is Funny\n", strlen("Linux is Funny\n"));

        // Close the write end of the pipe
        close(pipe_fd[1]);
    } else {  // Parent process
        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Read and display messages from the pipe
        while (read(pipe_fd[0], buffer, sizeof(buffer)) > 0) {
            printf("Parent received: %s", buffer);
        }

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Wait for the child process to finish
        wait(NULL);
    }

    return 0;
}
