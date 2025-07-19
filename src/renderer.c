#include "renderer.h"
#include<stdio.h>
#include <math.h>
#include "math_utils.h"

renderer_state rend_state;

bool renderer_init(renderer_init_info init_info)
{
    if (init_info.width == 0 || init_info.height == 0) {
        printf("Width or Height can not be zero!");
        return false;
    }

    rend_state.width = init_info.width;
    rend_state.height = init_info.height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialise SDL\n");
        return false;
    }

    rend_state.window = SDL_CreateWindow(init_info.window_name, rend_state.width, rend_state.height, SDL_WINDOW_RESIZABLE);
    if(rend_state.window == 0) return false;

    rend_state.sdl_renderer = SDL_CreateRenderer(rend_state.window, 0);
    if(rend_state.sdl_renderer == 0) return false;

    for (int i = 0; i < FRAMEBUFFER_COUNT ; i++){
        rend_state.textures[i] = SDL_CreateTexture(rend_state.sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, rend_state.width, rend_state.height);
        if(rend_state.textures[i] == 0) return false;
    }

    rend_state.current_buffer = 0;
    rend_state.framebuffer = 0;

    return true;
}

void renderer_sthutdown()
{
    SDL_DestroyWindow(rend_state.window);
    SDL_Quit();
}

void *renderer_begin_frame()
{   
    if(rend_state.framebuffer) return rend_state.framebuffer;
    void* pixels = 0;
    int pitch;
    if(!SDL_LockTexture(rend_state.textures[rend_state.current_buffer], 0, &pixels, &pitch)){
        printf("Texture lock failed: %s \n", SDL_GetError());
        return 0;
    }
    rend_state.framebuffer_pitch = pitch/sizeof(unsigned int);
    rend_state.framebuffer = (unsigned int*)pixels;
    
    return rend_state.framebuffer;
}

void renderer_end_frame()
{   
    if(rend_state.framebuffer){
        SDL_UnlockTexture(rend_state.textures[rend_state.current_buffer]);
        rend_state.framebuffer = 0;
    }
    SDL_RenderClear(rend_state.sdl_renderer);
    SDL_RenderTextureRotated(rend_state.sdl_renderer, rend_state.textures[rend_state.current_buffer], 0, 0, 0.0, 0, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(rend_state.sdl_renderer);
    rend_state.current_buffer = (rend_state.current_buffer + 1)%FRAMEBUFFER_COUNT;
}

void renderer_fill_colour(unsigned int colour) {
    if(!rend_state.framebuffer) {
        printf("Framebuffer cannot be null pointer.");
    }
    else {
        for(int y = 0; y < rend_state.height ; y++){
            for(int x = 0; x < rend_state.width ; x++){
                rend_state.framebuffer[y * rend_state.framebuffer_pitch + x] = colour;
            }
        }
    }
}

void renderer_draw_line(int x0, int y0, int x1, int y1, unsigned int colour){
    if(!rend_state.framebuffer) {
        printf("Framebuffer cannot be null pointer.");
    }
    else {
        bool steep = false;
        if (abs(x0 - x1) < abs(y0 - y1)){
            swap(&x0 , &y0);
            swap(&x1, &y1);
            steep = true;
        }
        if (x0 > x1){
            swap(&x0, &x1);
            swap(&y0, &y1);
        }
        int dx = x1 - x0;
        int dy = abs(y1 - y0);
        int error2 = 0;
        int derror2 = dy*2;
        int y = y0;
        int ystep = (y1 > y0) ? 1 : -1;
        for (int x = x0; x <= x1; ++x){
            if (steep){
                if (y >= 0 && y < rend_state.width && x >= 0 && x < rend_state.height){
                    rend_state.framebuffer[x* rend_state.framebuffer_pitch + y] = colour;
                }
            }
            else{
                if (x >=0 && x < rend_state.width && y >= 0 && y < rend_state.height){
                    rend_state.framebuffer[y*rend_state.framebuffer_pitch + x] = colour;
                }
            }
            error2 += derror2;
            if (error2 > dx*2){
                y += ystep;
                error2 -= dx*2;
            }
        }

    }

}