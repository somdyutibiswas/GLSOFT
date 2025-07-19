#include<stdio.h>

#include <application.h>

int main(){
    printf("Booting graphics library software\n");
    application_init_info init_info;
    init_info.app_name = "GLSOFT";
    init_info.width = 1200;
    init_info.height = 800;
    if (!application_init(init_info)) return 1;

    if (!application_run()) return 1;
    
    printf("Shutting down graphics library software\n");
    application_shutdown();

    return 0;
}