#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>   
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int rc = fork();
    if(rc < 0) {
        printf("fork error !\n");
        exit(1);
    } else if(rc == 0) {
        printf("(pid: %d)I'm child\n", getpid());
    } else {
        sleep(2);
        printf("(pid: %d, parent of %d) I'm parent\n", getpid(), rc);
    }
    return 0;
}
