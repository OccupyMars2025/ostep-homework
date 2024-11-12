/*
gcc -g -o use_realloc use_realloc.c
valgrind --leak-check=yes ./use_realloc 

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    size_t size;
    size_t capacity;
} Vector;

// Initialize a vector
void init_vector(Vector *v) {
    v->size = 0;
    v->capacity = 2;
    v->array = (int *)malloc(v->capacity * sizeof(int));
    if (v->array == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

// Add an element to the vector
void add_element(Vector *v, int element) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->array = (int *)realloc(v->array, v->capacity * sizeof(int));
        if (v->array == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    v->array[v->size++] = element;
}

// Free the vector
void free_vector(Vector *v) {
    free(v->array);
}

// Print the vector's elements
void print_vector(const Vector *v) {
    for (size_t i = 0; i < v->size; i++) {
        printf("%d ", v->array[i]);
    }
    printf("\n");
}

int main() {
    Vector v;
    init_vector(&v);

    // Add elements to the vector
    for (int i = 0; i < 10; i++) {
        add_element(&v, i);
    }

    // Print the vector
    print_vector(&v);

    // Free the memory
    free_vector(&v);

    return 0;
}
