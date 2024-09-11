// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main() {
//     int rc = fork();

//     if (rc < 0) {
//         // Fork failed
//         perror("fork error");
//         exit(1);
//     } else if (rc == 0) {
//         // Child process
//         printf("Child: Before closing stdout\n");  // This will be printed

//         // Close standard output
//         close(STDOUT_FILENO);

//         // Attempt to print again
//         printf("Child: After closing stdout\n");   // This will NOT be printed

//         exit(0);
//     } else {
//         // Parent process
//         wait(NULL);  // Wait for the child to finish
//         printf("Parent: Child has finished\n");
//     }

//     return 0;
// }





#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main() {
    int rc = fork();

    if (rc < 0) {
        // Fork failed
        perror("fork");
        exit(1);
    } else if (rc == 0) {
        // Child process
        printf("(pid: %d) I'm child\n", getpid());

        // Close stdout
        close(STDOUT_FILENO);

        // Open a file to redirect stdout
        int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        if (fd < 0) {
            perror("open");
            exit(1);
        }

        // Redirect stdout to the file
        dup2(fd, STDOUT_FILENO);  // Now stdout points to 'output.txt'
        printf("fd = %d, STDOUT_FILENO = %d\n", fd, STDOUT_FILENO);
        
        // No, if you close fd, you will close the stdout again
        // close(fd);                // Close the original file descriptor (no longer needed)


        // Attempt to print after redirecting stdout
        printf("This output will go to the file 'output.txt'\n");
        fflush(stdout);           // Force flush to make sure it writes to the file

        exit(0);
    } else {
        // Parent process
        wait(NULL);  // Wait for the child to finish
        printf("Parent: Child has finished\n");
    }

    return 0;
}
