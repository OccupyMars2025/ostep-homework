#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define ITERATIONS 1000000  // Number of iterations

int main() {
    struct timeval start, end;
    int fd[2];
    char buffer[0];  // Empty buffer for 0-byte read
    pipe(fd);        // Create a pipe (used for the 0-byte read)

    // Get start time
    gettimeofday(&start, NULL);

    // Perform the 0-byte read system call multiple times
    for (int i = 0; i < ITERATIONS; i++) {
        read(fd[0], buffer, 0);
    }

    // Get end time
    gettimeofday(&end, NULL);

    // Calculate elapsed time
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    // Output the average time per system call
    printf("Average time per system call: %lf microseconds\n", (elapsed / ITERATIONS) * 1e6);

    return 0;
}
