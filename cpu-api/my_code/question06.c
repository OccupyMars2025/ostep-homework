#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>  // For waitpid()
#include <unistd.h>    // For fork()

int main() {
    int rc = fork();

    if (rc < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        printf("Hello, I am the child process (pid: %d)\n", getpid());
        sleep(2);  // Simulate some work
        printf("Child process finishing...\n");
        exit(0);   // Child exits
    } else {
        // Parent process
        printf("Hello, I am the parent process (pid: %d)\n", getpid());

        // Parent waits for the specific child process to terminate
        int status;
        int wc = waitpid(rc, &status, 0);  // Wait for the child process with PID `rc`
        if (wc == rc) {
            if (WIFEXITED(status)) {
                printf("Parent process: child (pid: %d) finished with exit status %d\n", wc, WEXITSTATUS(status));
            } else {
                printf("Parent process: child (pid: %d) did not exit normally\n", wc);
            }
        } else {
            printf("Parent process: Error while waiting for child\n");
        }

        // int wc = waitpid(rc, &status, WNOHANG);
        // if (wc == 0) {
        //     printf("Child process has not terminated yet.\n");
        // } else if (wc == rc) {
        //     printf("Child process terminated.\n");
        // }

    }

    return 0;
}
