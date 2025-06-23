#pragma once
#include <SDL3/SDL.h>

#define FRAMEBUFFER_COUNT 2

typedef struct renderer_init_info
{
    const char* window_name;
    unsigned int width;
    unsigned int height;
}renderer_init_info;

typedef struct renderer_state
{
    SDL_Window* window;
    SDL_Renderer* sdl_renderer;
    SDL_Texture* textures[FRAMEBUFFER_COUNT];
    int current_buffer;
    unsigned int* framebuffer;

    unsigned int width;
    unsigned int height;
    int framebuffer_pitch;

}renderer_state;

bool renderer_init(renderer_init_info init_info);
void renderer_sthutdown();
void* renderer_begin_frame();
void renderer_end_frame();

void renderer_fill_colour(unsigned int colour);

