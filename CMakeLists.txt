cmake_minimum_required(VERSION 3.25)

project(raycasting)

find_library(SDL2 required)

add_executable(${PROJECT_NAME} src/main.c src/config.h)
target_link_libraries(${PROJECT_NAME} SDL2)