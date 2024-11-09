#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILES 100

// Function to compare file sizes
int compare_file_sizes(const void *a, const void *b) {
    struct stat stat_a, stat_b;

    // Get the file size of the first file
    if (stat(*(const char **)a, &stat_a) == -1) {
        perror("Error getting file size");
        return 0;
    }

    // Get the file size of the second file
    if (stat(*(const char **)b, &stat_b) == -1) {
        perror("Error getting file size");
        return 0;
    }

    // Compare the file sizes
    return stat_a.st_size - stat_b.st_size;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    // Sort the file names based on their size
    qsort(&argv[1], argc - 1, sizeof(char *), compare_file_sizes);

    printf("Files sorted by size in ascending order:\n");

    // Display the sorted filenames
    for (int i = 1; i < argc; i++) {
        struct stat stat_buf;
        if (stat(argv[i], &stat_buf) == -1) {
            perror("Error getting file size");
            continue;
        }
        printf("%s (Size: %ld bytes)\n", argv[i], stat_buf.st_size);
    }

    return 0;
}
