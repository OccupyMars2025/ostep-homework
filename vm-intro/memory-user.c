/*
chapter 13, homework  

gcc -o memory-user memory-user.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Function to simulate memory access
void touch_memory(char *array, size_t size_in_mb) {
    size_t size = size_in_mb * 1024 * 1024; // Convert MB to bytes
    for (size_t i = 0; i < size; i++) {
        array[i] = i % 256;  // Just write some data to the array to simulate access
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <memory size in MB> [<duration in seconds>]\n", argv[0]);
        return 1;
    }

    // Get the memory size in MB from the command line
    size_t memory_size_in_mb = atoi(argv[1]);

    // Check if a duration is provided, otherwise run indefinitely
    int duration = -1;  // -1 means run indefinitely
    if (argc >= 3) {
        duration = atoi(argv[2]);
    }

    // Print the PID of this process
    printf("Process ID (PID): %d\n", getpid());

    // Allocate memory on the heap
    char *memory_array = (char *)malloc(memory_size_in_mb * 1024 * 1024);
    if (memory_array == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }
    printf("Allocated %zu MB of memory\n", memory_size_in_mb);

    time_t start_time = time(NULL);
    while (1) {
        touch_memory(memory_array, memory_size_in_mb);  // Access the memory

        // If duration is provided, check if the time limit has been reached
        if (duration != -1 && (time(NULL) - start_time) >= duration) {
            break;
        }
    }

    // Free the allocated memory before exiting
    free(memory_array);
    printf("Memory released after running for %d seconds\n", (duration == -1) ? (int)(time(NULL) - start_time) : duration);

    return 0;
}
