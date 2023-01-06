cmake_minimum_required(VERSION 3.24)
project(Project1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Project1 main.c calculate.c Quit.c)
target_link_libraries(Project1 mingw32)
target_link_libraries(Project1 SDL2main)
target_link_libraries(Project1 SDL2)
target_link_libraries(Project1 SDL2_image)
target_link_libraries(Project1 SDL2_ttf)