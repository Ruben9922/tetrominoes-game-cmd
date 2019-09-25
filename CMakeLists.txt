cmake_minimum_required(VERSION 3.14)
project(tetrominoes_game_cmd)

set(CMAKE_CXX_STANDARD 14)

add_executable(tetrominoes_game_cmd main.cpp)
target_link_libraries(${PROJECT_NAME} ncurses)

# Include MathFu in this project with test and benchmark builds disabled
# then add MathFu compiler flags to the mygame build target.
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
add_subdirectory(../mathfu mathfu)
mathfu_configure_flags(${PROJECT_NAME})
