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

    state.sdl_renderer = SDL_CreateRenderer(state.window, 0);
    if(state.sdl_renderer == 0) return false;

    for (int i = 0; i < FRAMEBUFFER_COUNT ; i++){
        state.textures[i] = SDL_CreateTexture(state.sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, state.width, state.height);
        if(state.textures[i] == 0) return false;
    }

    state.current_buffer = 0;
    state.framebuffer = 0;

    return true;
}

void renderer_sthutdown()
{
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}

void *renderer_begin_frame()
{   
    if(state.framebuffer) return state.framebuffer;
    void* pixels = 0;
    int pitch;
    if(!SDL_LockTexture(state.textures[state.current_buffer], 0, &pixels, &pitch)){
        printf("Texture lock failed: %s \n", SDL_GetError());
        return 0;
    }
    state.framebuffer_pitch = pitch/sizeof(unsigned int);
    state.framebuffer = (unsigned int*)pixels;
    
    return state.framebuffer;
}

void renderer_end_frame()
{   
    if(state.framebuffer){
        SDL_UnlockTexture(state.textures[state.current_buffer]);
        state.framebuffer = 0;
    }
    SDL_RenderClear(state.sdl_renderer);
    SDL_RenderTextureRotated(state.sdl_renderer, state.textures[state.current_buffer], 0, 0, 0.0, 0, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(state.sdl_renderer);
    state.current_buffer = (state.current_buffer + 1)%FRAMEBUFFER_COUNT;
}

void renderer_fill_colour(unsigned int colour) {
    if(!state.framebuffer) {
        printf("Framebuffer cannot be null pointer.");
    }
    else {
        for(int y = 0; y < state.height ; y++){
            for(int x = 0; x < state.width ; x++){
                state.framebuffer[y * state.framebuffer_pitch + x] = colour;
            }
        }
    }
}