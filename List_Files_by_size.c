#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    long min_size;
    int found = 0;

    // Get minimum file size from user
    printf("Enter minimum file size in bytes: ");
    if (scanf("%ld", &min_size) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    // Open current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Failed to open directory");
        return 1;
    }

    printf("\nFiles larger than %ld bytes:\n", min_size);
    printf("--------------------------------\n");

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Get file statistics
        if (stat(entry->d_name, &file_stat) == -1) {
            fprintf(stderr, "Cannot stat %s: %s\n", 
                    entry->d_name, strerror(errno));
            continue;
        }

        // Check if it's a regular file and size condition
        if (S_ISREG(file_stat.st_mode) && file_stat.st_size > min_size) {
            printf("%-30s %10ld bytes\n", entry->d_name, file_stat.st_size);
            found++;
        }
    }

    // Print summary
    printf("--------------------------------\n");
    printf("Total files found: %d\n", found);

    closedir(dir);
    return 0;
}