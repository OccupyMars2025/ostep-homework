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
    // add file permission
    int fd = open("test02.txt", O_CREAT | O_RDWR, 0644);

    int rc = fork();
    if(rc < 0) {
        printf("fork error !\n");
        exit(1);
    } else if(rc == 0) {
        printf("(pid: %d) fd: %d\n", getpid(), fd);
        char child_message[50] = "hello, I'm child";
        write(fd, child_message, strlen(child_message));
    } else {
        printf("(pid: %d, parent of %d) fd: %d\n", getpid(), rc, fd);

        char parent_message[50] = "hi, I'm parent";
        write(fd, parent_message, strlen(parent_message));
        wait(NULL);
        close(fd);
    }
    return 0;
}
