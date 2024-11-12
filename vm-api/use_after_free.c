/*
gcc -g -o use_after_free use_after_free.c
valgrind --leak-check=yes ./use_after_free
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int*) malloc(100 * sizeof(int));  // Allocate memory for 100 integers
    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    data[0] = 42;  // Set the first element to some value

    free(data);  // Free the allocated memory

    // Attempt to access and print a freed element
    printf("Value of data[0]: %d\n", data[0]);

    return 0;
}
