#include "application.h"

application_state state;

bool application_init(application_init_info init_info) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialise SDL\n");
        return false;
    }

    state.window = SDL_CreateWindow(init_info.app_name, init_info.width, init_info.height, SDL_WINDOW_RESIZABLE);
    if(state.window == 0) return false;

    return true;
}

bool application_run()
{
    state.running = true;
    SDL_Event event ;

    while(state.running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT) {
                state.running = false;
            }
        }
        // Render logic
    }
    return false;
}

void application_shutdown()
{
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}
