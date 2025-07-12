#include "application.h"
#include<SDL3/SDL.h>
#include <renderer.h>
#include <math.h>
#include "math_utils.h"

#define AXIS_LENGTH 1024

application_state state;

bool application_init(application_init_info init_info) {
    renderer_init_info renderer_info;
    renderer_info.window_name = init_info.app_name;
    renderer_info.width = init_info.width;
    renderer_info.height = init_info.height;
    if (!renderer_init(renderer_info)) return false;
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
        
        // TODO: temp
        static float a = 0.0f;
        static float multiplier = 0.1f;
        if (a > 64.0f) {
            multiplier *= -1.0f;
        } else {
            a += multiplier;
        }
        
        // TODO: end temp
        unsigned int cyan = 0xFFC8E9C9;
        // renderer_fill_colour(cyan);
        // renderer_draw_line(200, 50, 500, 30, cyan);
        int x_axis[AXIS_LENGTH];
        int y_axis[AXIS_LENGTH];
        for (int i=0; i<AXIS_LENGTH; i++) {
            x_axis[i] = i;
            y_axis[i] = sin(x_axis[i]/a) * 100 + 256;
        }
        graph_plot(x_axis, y_axis, AXIS_LENGTH, cyan);

        renderer_end_frame();
    }
    return false;
}

void application_shutdown()
{
    renderer_sthutdown();
}
