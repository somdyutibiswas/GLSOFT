#include "application.h"
#include<SDL3/SDL.h>
#include <renderer.h>

application_state state;

bool application_init(application_init_info init_info) {
    renderer_init_info renderer_info;
    renderer_info.window_name = init_info.app_name;
    renderer_info.width = init_info.width;
    renderer_info.height = init_info.height;
    renderer_init(renderer_info);
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
        if (renderer_begin_frame() == 0) continue;

        renderer_end_frame();
    }
    return false;
}

void application_shutdown()
{
    renderer_sthutdown();
}
