#include "application.h"
#include<SDL3/SDL.h>
#include <renderer.h>
#include <math.h>
#include "math_utils.h"

#define AXIS_LENGTH 1024

application_state app_state;

bool application_init(application_init_info init_info) {
    renderer_init_info renderer_info;
    renderer_info.window_name = init_info.app_name;
    renderer_info.width = init_info.width;
    renderer_info.height = init_info.height;
    if (!renderer_init(renderer_info)) return false;
    app_state.width = init_info.width;
    app_state.height = init_info.height;
    return true;
}

bool application_run()
{
    app_state.running = true;
    SDL_Event event ;

    int data[100];
    generate_shuffled_array(data, 100);

    while(app_state.running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT) {
                app_state.running = false;
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
        // GRID
        unsigned int color = 0x44AAAAAA;
        grid_draw(app_state.width, app_state.height, color);

        unsigned int cyan = 0xFFC8E9C9;
        // // renderer_fill_colour(cyan);
        // // renderer_draw_line(200, 50, 500, 30, cyan);
        // int x_axis[AXIS_LENGTH];
        // int y_axis[AXIS_LENGTH];
        // for (int i=0; i<AXIS_LENGTH; i++) {
        //     x_axis[i] = i;
        //     y_axis[i] = sin(x_axis[i]/a) * 100 + 256;
        // }
        // graph_plot(x_axis, y_axis, AXIS_LENGTH, cyan);

        // rect_draw(200, 100, 300, 200, cyan);
        
        for (int i = 0 ; i < 100; i++){
            bar_plot(i, data[i], cyan);
        }
        

        renderer_end_frame();
    }
    return false;
}

void application_shutdown()
{
    renderer_sthutdown();
}
