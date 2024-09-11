#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2]; // pipefd[0] for reading, pipefd[1] for writing
    pid_t cpid1, cpid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // First child process (writes to pipe)
    cpid1 = fork();
    if (cpid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid1 == 0) { // Child 1
        // Close the read end of the pipe
        close(pipefd[0]);
        printf("(pid: %d) before dup2() I am child 1, pipefd:[%d, %d], STDOUT_FILENO=%d\n", getpid(), pipefd[0], pipefd[1], STDOUT_FILENO);
        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        printf("(pid: %d) I am child 1, pipefd:[%d, %d], STDOUT_FILENO=%d\n", getpid(), pipefd[0], pipefd[1], STDOUT_FILENO);

        // Close the write end of the pipe after redirecting
        close(pipefd[1]);

        // Execute a command, for example, "ls"
        execlp("ls", "ls", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Second child process (reads from pipe)
    cpid2 = fork();
    if (cpid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid2 == 0) { // Child 2
        // Close the write end of the pipe
        close(pipefd[1]);

        // Redirect stdin to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);

        // Close the read end of the pipe after redirecting
        close(pipefd[0]);

        // Execute a command, for example, "wc -l" (word count)
        execlp("wc", "wc", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent process
    // Close both ends of the pipe as parent doesn't need them
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both children to finish
    wait(NULL);
    wait(NULL);

    return 0;
}
