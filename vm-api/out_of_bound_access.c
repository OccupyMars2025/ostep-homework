/*
gcc -g -o out_of_bound_access out_of_bound_access.c
valgrind --leak-check=yes  ./out_of_bound_access
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int*) malloc(100 * sizeof(int));  // Allocate memory for 100 integers
    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    data[100] = 0;  // This will cause an error (out-of-bounds access)
    
    free(data);  // Free the allocated memory
    return 0;
}
