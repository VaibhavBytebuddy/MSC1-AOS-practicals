#include <stdio.h>

int main() {
    // Open a file for writing (the file will be created if it doesn't exist)
    FILE *file = freopen("output.txt", "w", stdout);

    if (file == NULL) {
        perror("Error redirecting stdout to file");
        return 1;
    }

    // Now all the printf statements will be written to output.txt
    printf("This is a test message written to the file.\n");
    printf("Redirection of standard output is successful!\n");

    // Close the file after writing
    fclose(file);

    return 0;
}
