#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        printf("fork error !\n");
        exit(1);
    } else if(0 == rc)  {
        printf("(pid: %d) x = %d\n", getpid(), x);
        x = 888;
        printf("(pid: %d) x = %d\n", getpid(), x);
    } else {
        printf("(pid: %d, parent of %d) x = %d\n", getpid(), rc, x);
        x = 999;
        printf("(pid: %d, parent of %d) x = %d\n", getpid(), rc, x);
        int wc = wait(NULL);
        printf("(pid: %d, parent of %d) x = %d, wc = %d\n", getpid(), rc, x, wc);
    }
    return 0;
}
