#include<stdio.h>
#include<SDL3/SDL.h>

int main(){
    printf("Booting graphics library software\n");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialise SDL\n");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("GLSOFT", 800, 600, SDL_WINDOW_RESIZABLE);
    if(window == 0) return 1;

    bool running = true;
    SDL_Event event ;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
        // Render logic
    }

    printf("Shutting down graphics library software\n");
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}