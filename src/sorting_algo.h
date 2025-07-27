#pragma once
#include<stdbool.h>

bool bubble_sort(int* array, unsigned int size);

typedef struct{
    int width;
    int i;
    int size;
    int sorted;
}merge_sort_state;
void merge_sort(int* array, unsigned int size, int* aux, unsigned int aux_size,merge_sort_state* state);