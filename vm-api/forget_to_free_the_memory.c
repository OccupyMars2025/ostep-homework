/*
gcc -g -o forget_to_free_the_memory forget_to_free_the_memory.c 

*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int*) malloc(sizeof(int) * 10);  // Allocate memory for 10 integers
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // (Do something with the allocated memory)
    ptr[0] = 100;  // Example usage

    // Forgot to free(ptr)
    return 0;  // Memory leak happens here as we don't call free(ptr)
}
