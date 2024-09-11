#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int rc = fork();

    if (rc < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        printf("Hello, I am the child process (pid: %d)\n", getpid());

        // Child tries to wait for its own children (but it has none)
        int wc = wait(NULL);
        if (wc == -1) {
            printf("Child process (pid: %d): No children to wait for\n", getpid());
        }

        sleep(2);
        printf("Child process finishing...\n");
        exit(0);
    } else {
        // Parent process
        printf("Hello, I am the parent process (pid: %d)\n", getpid());

        // Parent waits for the child to terminate
        int wc = wait(NULL);
        printf("Parent process: child (pid: %d) finished\n", wc);
    }

    return 0;
}
