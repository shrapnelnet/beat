cmake_minimum_required(VERSION 3.25)
project(beat C)

set(CMAKE_C_STANDARD 17)

add_executable(beat main.c)
target_link_libraries(beat m)