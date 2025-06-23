#include "renderer.h"
#include<stdio.h>

renderer_state state;

bool renderer_init(renderer_init_info init_info)
{
    if (init_info.width == 0 || init_info.height == 0) {
        printf("Width or Height can not be zero!");
        return false;
    }

    state.width = init_info.width;
    state.height = init_info.height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialise SDL\n");
        return false;
    }

    state.window = SDL_CreateWindow(init_info.window_name, state.width, state.height, SDL_WINDOW_RESIZABLE);
    if(state.window == 0) return false;

    return true;
}

void renderer_sthutdown()
{
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}

void *renderer_begin_frame()
{
    return 0;
}

void renderer_end_frame()
{
}
