#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct Vector
{
    int*    data;
    size_t  item_count;
    size_t  capacity;
} Vector;

Vector* createVector(int capacity) {
    Vector* v = malloc(sizeof(Vector));
    if(!v) return NULL;

    v->capacity     = capacity > 0 ? capacity : 10;
    v->item_count   = 0;
    v->data         = calloc(v->capacity, sizeof(int));
    
    if(!v->data) {
        free(v);
        return NULL;
    }
    return v;
}

int vectorResize(Vector* v, size_t capacity) {
    if(!v) return -1;
    if(capacity < v->item_count || capacity * sizeof(int) > SIZE_MAX || capacity < 1) return - 1;

    int* new_data = realloc(v->data, sizeof(int) * capacity);
    if(!new_data) return -1;

    v->data     = new_data;
    v->capacity = capacity;
    return 0;
}

int pushVector(Vector* v, int data) {
    if(!v) return -1;

    if(v->item_count >= v->capacity) {
        vectorResize(v, v->capacity * 2);
    }

    v->data[v->item_count++] = data;
    return 0;
}

void popVector(Vector* v) {
    if(v && v->item_count > 0)
    {
        v->item_count--;
        v->data[v->item_count] = 0;
    }
}

int vectorGetAt(Vector* v, size_t index) {
    if(!v || index >= v->item_count) {
        return NULL;
    }
    return v->data[index];
}

void destroyVector(Vector* v) {
    if(v) {
        free(v->data);
        free(v);
    }
}