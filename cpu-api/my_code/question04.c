#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to execute /bin/ls using various exec() calls
void use_execl() {
    printf("Using execl:\n");
    execl("/bin/ls", "ls", "-l", NULL);
    perror("execl failed");
}

void use_execle() {
    printf("Using execle:\n");
    char *env[] = { "HOME=/usr/home", "LOGNAME=home", NULL };
    // execle("/bin/ls", "ls", NULL, env);
    execle("/bin/lfergrewefs", "ls", NULL, env);
    perror("execle failed");
}

void use_execlp() {
    printf("Using execlp:\n");
    execlp("ls", "ls", NULL);  // Looks for 'ls' in the PATH environment
    perror("execlp failed");
}

void use_execv() {
    printf("Using execv:\n");
    char *args[] = { "ls", NULL };
    execv("/bin/ls", args);
    perror("execv failed");
}

void use_execvp() {
    printf("Using execvp:\n");
    char *args[] = { "ls", NULL };
    execvp("ls", args);  // Looks for 'ls' in the PATH environment
    perror("execvp failed");
}

// void use_execvpe() {
//     printf("Using execvpe:\n");
//     char *args[] = { "ls", NULL };
//     char *env[] = { "HOME=/usr/home", "LOGNAME=home", NULL };
//     execvpe("ls", args, env);  // Looks for 'ls' in the PATH environment and allows custom environment
//     perror("execvpe failed");
// }

int main() {
    int rc;

    // Forking a child process
    rc = fork();

    if (rc < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // In the child process, try one of the exec calls
        // Uncomment the one you want to test:
        
        // use_execl();
        // use_execle();
        // use_execlp();
        // use_execv();
        use_execvp();
        // use_execvpe();

        // If exec fails, we reach this point and the following will be executed.
        // If exec succeeds, this will never be printed because the process will be replaced.
        printf("(pid: %d) I'm child\n", getpid());
        exit(1);  
    } else {
        // In the parent process, wait for the child to finish
        int wc = wait(NULL);
        printf("Parent (pid: %d) finished waiting for child (wc: %d)\n", (int)getpid(), wc);
    }

    return 0;
}
