cmake_minimum_required(VERSION 4.1)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp)

if(WIN32)
    target_compile_definitions(untitled PRIVATE _WIN32_WINNT=0x0501 WINVER=0x0501)
    target_link_options(untitled PRIVATE -Wl,--subsystem,console:5.01)
endif()