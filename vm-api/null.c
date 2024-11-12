/*
gcc -o null null.c

Segmentation fault (core dumped)


gcc -g -o null null.c

gdb null
Once inside GDB, you can start the program by typing run.

Program received signal SIGSEGV, Segmentation fault.
0x000055555555513d in main () at null.c:16
16	    *ptr = 5;         // Dereference the NULL pointer (this will cause a crash)
(gdb)


*/

#include <stdio.h>

int main() {
    int *ptr = NULL;  // Initialize pointer to NULL
    *ptr = 5;         // Dereference the NULL pointer (this will cause a crash)
    return 0;
}
