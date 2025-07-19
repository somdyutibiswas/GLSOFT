#pragma once

#define GRID_SIZE 8

void swap(int* a, int* b);
void graph_plot(int* data_x, int* data_y, int length, unsigned int colour);
void grid_draw(int width, int height, unsigned int colour);
void rect_draw(int x1 , int y1, int x2, int y2, unsigned int colour);
void bar_plot(int x , int h, unsigned int colour);
void generate_shuffled_array(int* arr, int size);