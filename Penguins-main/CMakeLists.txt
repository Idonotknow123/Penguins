cmake_minimum_required(VERSION 3.29)
project(penguins-103-e C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER gcc)
set(SOURCES
        main.c
        grid.c
        print.c
        play.c
        valid_check.c
        autonomous_mode.c
        autonomous_output.c
        unit_test.c
        algorithm.c
)

add_executable(game ${SOURCES})

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries(game m)