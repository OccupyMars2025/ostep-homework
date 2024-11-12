/*
gcc -g -o pass_a_funny_argument_to_free pass_a_funny_argument_to_free.c 
valgrind --leak-check=yes ./pass_a_funny_argument_to_free
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int*) malloc(100 * sizeof(int));  // Allocate memory for 100 integers
    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Pass a pointer in the middle of the array to free (this is incorrect)
    free(&data[50]);

    return 0;
}
