#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// Function to print the file type
void identify_file_type(const char *path) {
    struct stat statbuf;

    // Get the file status
    if (stat(path, &statbuf) == -1) {
        perror("stat");
        return;
    }

    // Check the file type
    if (S_ISDIR(statbuf.st_mode)) {
        printf("The file is a Directory.\n");
    }
    else if (S_ISCHR(statbuf.st_mode)) {
        printf("The file is a Character device.\n");
    }
    else if (S_ISBLK(statbuf.st_mode)) {
        printf("The file is a Block device.\n");
    }
    else if (S_ISREG(statbuf.st_mode)) {
        printf("The file is a Regular file.\n");
    }
    else if (S_ISFIFO(statbuf.st_mode)) {
        printf("The file is a FIFO (Named pipe).\n");
    }
    else if (S_ISLNK(statbuf.st_mode)) {
        printf("The file is a Symbolic link.\n");
    }
    else if (S_ISSOCK(statbuf.st_mode)) {
        printf("The file is a Socket.\n");
    }
    else {
        printf("The file type is unknown.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    // Call the function to identify the file type
    identify_file_type(argv[1]);

    return 0;
}
