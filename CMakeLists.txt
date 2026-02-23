cmake_minimum_required(VERSION 4.1)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp)

add_definitions(
        -D_WIN32_WINNT=0x0501   # XP
        -DWINVER=0x0501
        -DNTDDI_VERSION=0x05010300
)

target_link_options(untitled PRIVATE
        -static-libgcc
        -static-libstdc++
        -static
        -Wl,--subsystem,console   # or windows if GUI app
)

if(WIN32)
    target_compile_definitions(untitled PRIVATE _WIN32_WINNT=0x0501 WINVER=0x0501)
    target_link_options(untitled PRIVATE -Wl,--subsystem,console:5.01)
endif()