#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    char file_name[100];
    int file_found = 0;

    // Ask the user to input the file name to search
    printf("Enter the file name to search: ");
    scanf("%s", file_name);

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    // Search for the file in the directory
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, file_name) == 0) {
            file_found = 1;
            break;
        }
    }

    // Display the result
    if (file_found) {
        printf("File '%s' is present in the current directory.\n", file_name);
    } else {
        printf("File '%s' is not found in the current directory.\n", file_name);
    }

    // Close the directory
    closedir(dir);
    return 0;
}
