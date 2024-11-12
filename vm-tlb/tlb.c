/*
./tlb <number_of_pages> <number_of_trials>
*/

#define _GNU_SOURCE       // Enable GNU extensions for sched_setaffinity
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sched.h>
#include <pthread.h>


#define PAGESIZE 4096 // Assuming a 4KB page size


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_pages> <number_of_trials>\n", argv[0]);
        return 1;
    }

    int NUMPAGES = atoi(argv[1]);
    int NUMTRIALS = atoi(argv[2]);

    if (NUMPAGES <= 0 || NUMTRIALS <= 0) {
        fprintf(stderr, "Number of pages and trials must be positive integers.\n");
        return 1;
    }

    cpu_set_t cpuset;               // Define a CPU set
    CPU_ZERO(&cpuset);               // Initialize it to be empty
    CPU_SET(0, &cpuset);             // Pin to CPU 0 (or any other CPU you prefer)

    // Set CPU affinity for the calling process
    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) != 0) {
        perror("sched_setaffinity");
        return 1;
    }

    // Continue with your TLB measurement code
    printf("Running on CPU 0\n");

    int jump = PAGESIZE / sizeof(int); // Number of integers per page
    int array_size = NUMPAGES * jump;  // Total number of integers to allocate

    // Allocate memory for the array
    int *a = malloc(array_size * sizeof(int));
    if (a == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Initialize array to avoid any impact from lazy allocation
    for (int i = 0; i < array_size; i++) {
        a[i] = 0;
    }

    struct timeval start, end;
    double total_time = 0.0;

    for (int t = 0; t < NUMTRIALS; t++) {
        gettimeofday(&start, NULL); // Start timing

        // Loop through the array, touching each page
        for (int i = 0; i < NUMPAGES * jump; i += jump) {
            a[i] += 1; // Access each page
        }

        gettimeofday(&end, NULL); // End timing

        // Calculate the elapsed time in microseconds
        double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
        total_time += time_taken;
    }

    // Calculate the average time per page access
    double avg_time_per_access = total_time / (NUMPAGES * NUMTRIALS);

    printf("Average time per page access: %.2f nanoseconds\n", avg_time_per_access * 1e3);

    free(a);
    return 0;
}
