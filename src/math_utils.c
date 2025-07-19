#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math_utils.h"
#include "renderer.h"

void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

void graph_plot(int* data_x, int* data_y, int length, unsigned int colour) {
    if ( length <= 0){
        printf("Length cannot be zero or negative");
        return;
    }
    for (int index = 0 ; index < length - 1; index++){
        int x0 = data_x[index];
        int y0 = data_y[index];
        int x1 = data_x[index + 1];
        int y1 = data_y[index + 1];
        renderer_draw_line(x0, y0, x1, y1, colour);
    }
}

void grid_draw(int width, int height, unsigned int colour) {
    int line_count_x = width/GRID_SIZE;
    int line_count_y = height/GRID_SIZE;
    for (int xi = 0; xi < line_count_x; xi++){
        int x0 = xi*GRID_SIZE;
        int y0 = 0;
        int x1 = x0;
        int y1 = height;
        renderer_draw_line(x0, y0, x1, y1, colour);
    }
    for (int yi = 0; yi < line_count_y; yi++){
        int x0 = 0;
        int y0 = yi*GRID_SIZE;
        int x1 = width;
        int y1 = y0;
        
        renderer_draw_line(x0, y0, x1, y1, colour);
    }
}

void rect_draw(int x1 , int y1, int x2, int y2, unsigned int colour) {
    for ( int xi = 1 ; xi < (x2 - x1) - 1 ; xi ++){
        renderer_draw_line(x1 + xi , y2, x1+ xi, y1, colour);
    }
}
void bar_plot(int x , int h, unsigned int colour) {
    rect_draw(GRID_SIZE*x , GRID_SIZE*h, GRID_SIZE*(x +1), 0 , colour);
}

void generate_shuffled_array(int* arr, int size) {
    if (size <= 0) return;
    for (int i = 0; i < size ; i++){
        arr[i] = i;
    }
    static int seed = 0;
    if(!seed){
        srand((unsigned int)time(NULL));
        seed = 1;
    }
    for (int i = size - 1; i > 0; --i){
        int j = rand()%(i+1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}