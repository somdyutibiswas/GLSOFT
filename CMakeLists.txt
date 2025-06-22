cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD 20)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(GLSOFT)

add_executable(App
    src/main.c 
)

add_subdirectory(SDL)

target_include_directories(App PRIVATE
    src 
    SDL/include
)

target_link_libraries(App PRIVATE
    SDL3::SDL3-shared
)