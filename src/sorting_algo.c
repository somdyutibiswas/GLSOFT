#include "sorting_algo.h"

bool bubble_sort(int* array, unsigned int size){
    bool swapped = false;
    for (int i = 1; i < size; i++){
        if (array[i-1] > array[i]){
            int temp = array[i];
            array[i] = array[i-1];
            array[i-1] = temp;
            swapped = true;
        }
    }
    return swapped;
}

void merge_sort(int *array, unsigned int size, int* aux, unsigned int aux_size,merge_sort_state* state) {
    if (state->sorted) return;
    int left = state->i;
    int mid = left + state->width;  
    int right = left + 2*state->width;
    if (mid > size) mid = size;
    if (right > size) right = size;
    if (left < size && mid < right) {
        int i = left;
        int j = mid;
        int k = left;
        while (i < mid && j < right) {
            if (array[i] < array[j]) {
                aux[k++] = array[i++];
            }
            else {
                aux[k++] = array[j++];
            }
        }
        while (i< mid) aux[k++] = array[i++];
        while (j < right) aux[k++] = array[j++];
        for (i = left; i < right ; i++) array[i] = aux[i];
    } 
    state->i += 2*state->width;
    if (state->i >= size) {
        state->i = 0;
        state->width *= 2;
        if (state->width >= size) state->sorted = 1; 
    }
}
 