#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

// Function to print the resource limit
void print_limit(int resource, const char *name) {
    struct rlimit limit;
    if (getrlimit(resource, &limit) == 0) {
        printf("%s limits:\n", name);
        printf("  Soft limit: %ld\n", (long)limit.rlim_cur);
        printf("  Hard limit: %ld\n\n", (long)limit.rlim_max);
    } else {
        perror("getrlimit");
        exit(1);
    }
}

// Function to set a new soft limit for a resource
void set_soft_limit(int resource, rlim_t new_soft_limit) {
    struct rlimit limit;

    if (getrlimit(resource, &limit) != 0) {
        perror("getrlimit");
        exit(1);
    }

    limit.rlim_cur = new_soft_limit;  // Set the new soft limit
    if (setrlimit(resource, &limit) != 0) {
        perror("setrlimit");
        exit(1);
    }
}

int main() {
    // Display current limits for open files
    print_limit(RLIMIT_NOFILE, "Open files");
    
    // Set a new soft limit for open files (e.g., 1024)
    printf("Setting new soft limit for open files to 1024...\n");
    set_soft_limit(RLIMIT_NOFILE, 1024);
    print_limit(RLIMIT_NOFILE, "Open files");

    // Display current limits for virtual memory
    print_limit(RLIMIT_AS, "Virtual memory");

    // Set a new soft limit for virtual memory (e.g., 512 MB)
    printf("Setting new soft limit for virtual memory to 512 MB...\n");
    set_soft_limit(RLIMIT_AS, 512 * 1024 * 1024);  // 512 MB in bytes
    print_limit(RLIMIT_AS, "Virtual memory");

    return 0;
}
