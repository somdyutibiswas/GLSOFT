#include <stdio.h>
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