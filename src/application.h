#pragma once
#include <stdbool.h>

typedef struct application_init_info {
    const char* app_name;
    unsigned int width;
    unsigned int height;
} application_init_info;

typedef struct application_state
{
    bool running;
    unsigned int width;
    unsigned int height;
    
} application_state;

bool application_init(application_init_info init_info);
bool application_run();
void application_shutdown();
