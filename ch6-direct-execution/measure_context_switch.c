#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sched.h>     // For sched_setaffinity()
#include <pthread.h>   // For CPU_ZERO and CPU_SET
#include <string.h>    // For memset, if needed for some environments

#define ITERATIONS 100000  // Number of iterations

// Function to bind the process to a specific CPU
void bind_to_cpu(int cpu) {
    cpu_set_t set;
    CPU_ZERO(&set);           // Clear the CPU set
    CPU_SET(cpu, &set);       // Add the desired CPU to the set
    if (sched_setaffinity(0, sizeof(cpu_set_t), &set) == -1) {
        perror("sched_setaffinity failed");
    }
}

int main() {
    int pipe1[2], pipe2[2];
    pipe(pipe1);  // Pipe for communication
    pipe(pipe2);
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        bind_to_cpu(0);  // Bind child process to CPU 0
        char buf;
        for (int i = 0; i < ITERATIONS; i++) {
            read(pipe1[0], &buf, 1);  // Read from pipe1
            write(pipe2[1], &buf, 1);  // Write to pipe2
        }
    } else {  // Parent process
        bind_to_cpu(0);  // Bind parent process to CPU 0
        struct timeval start, end;
        char buf = 'x';

        // Get start time
        gettimeofday(&start, NULL);

        for (int i = 0; i < ITERATIONS; i++) {
            write(pipe1[1], &buf, 1);  // Write to pipe1
            read(pipe2[0], &buf, 1);  // Read from pipe2
        }

        // Get end time
        gettimeofday(&end, NULL);

        // Calculate elapsed time
        long seconds = end.tv_sec - start.tv_sec;
        long microseconds = end.tv_usec - start.tv_usec;
        double elapsed = seconds + microseconds * 1e-6;

        // Output the average time per context switch
        printf("Average time per context switch: %lf microseconds\n", (elapsed / (ITERATIONS * 2)) * 1e6);
    }

    return 0;
}
