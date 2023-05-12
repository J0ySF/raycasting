cmake_minimum_required(VERSION 3.25)

project(raycasting)

set(CMAKE_C_STANDARD 23)

if (EMSCRIPTEN)
    add_definitions(-DEMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else ()
    find_package(SDL2 REQUIRED)
endif ()

add_executable(${PROJECT_NAME} src/main.c src/config.h src/map.c src/map.h)

if (EMSCRIPTEN)
    target_compile_options(${PROJECT_NAME} PUBLIC "SHELL:-s USE_SDL=2")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-s USE_SDL=2 -s WASM=1 --preload-file ./assets")
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 m)
endif ()

install(TARGETS ${PROJECT_NAME})
