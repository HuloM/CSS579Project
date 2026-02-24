cmake_minimum_required(VERSION 4.1)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp)

target_link_options(untitled PRIVATE
        -static-libgcc
        -static-libstdc++
        -static
        -Wl,--subsystem,console   # or windows if GUI app
)