#pragma once
#include<SDL3/SDL.h>

typedef struct renderer_init_info
{
    const char* window_name;
    unsigned int width;
    unsigned int height;
}renderer_init_info;

typedef struct renderer_state
{
    SDL_Window* window;

    unsigned int width;
    unsigned int height;

}renderer_state;

bool renderer_init(renderer_init_info init_info);
void renderer_sthutdown();
void* renderer_begin_frame();
void renderer_end_frame();

