#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    int file_count = 0;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open current directory");
        return 1;
    }

    printf("Files in the current directory:\n");

    // Read and display each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Only consider regular files (ignore directories and hidden files)
        if (entry->d_type == DT_REG) {
            printf("%s\n", entry->d_name);
            file_count++;
        }
    }

    printf("\nTotal number of files: %d\n", file_count);

    // Close the directory
    closedir(dir);
    return 0;
}
