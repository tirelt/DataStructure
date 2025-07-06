#include <stdio.h>
#include <stdlib.h>

struct Vector{
    int *data;
    size_t size;
    size_t capacity;
};

struct Vector *createVector(size_t initial_capacity) {
    struct Vector *vec = (struct Vector *)malloc(sizeof(struct Vector));
    vec->data = (int *)malloc(initial_capacity * sizeof(int));
    vec->size = 0;
    vec->capacity = initial_capacity;
    return vec;
};

size_t vectorSize(struct Vector *vec) {
    if (!vec)
        return 0;
    return vec->size;
}

size_t vectorCapacity(struct Vector *vec) {
    if (!vec)
        return 0;
    return vec->capacity;
}

void resizeCapacity(struct Vector *vec, size_t new_capacity) {
    if (!vec)
        return;
    vec->capacity = new_capacity;
    vec->data = (int *)realloc(vec->data, vec->capacity * sizeof(int));
}
void vectorPushBack(struct Vector *vec, int value) {
    if (!vec)
        return;
    if (vec->size >= vec->capacity)
        resizeCapacity(vec, vec->capacity * 2);
    vec->data[vec->size++] = value;
}
void vectorPopBack(struct Vector *vec) {
    if (!vec || vec->size == 0)
        return;
    vec->size--;
    if (vec->size < vec->capacity / 4) 
        resizeCapacity(vec, vec->capacity / 2);
}

int vectorGet(struct Vector *vec, size_t index) {
    if (!vec || index >= vec->size)
        return -1; 
    return vec->data[index];
}

void vectorDelete(struct Vector *vec) {
    if (!vec)
        return;
    free(vec->data);
    free(vec);
}

int main(){
    struct Vector *vec = createVector(2);
    vectorPushBack(vec, 10);
    vectorPushBack(vec, 42);
    vectorPushBack(vec, 69);
    vectorPopBack(vec);
    vectorPushBack(vec, 690);
    printf("Size: %zu\n", vectorSize(vec));
    printf("Size: %zu\n", vectorCapacity(vec));
    printf("2th element: %d\n", vectorGet(vec, 2));
    vectorDelete(vec);
    return 0;
}