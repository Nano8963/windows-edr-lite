cmake_minimum_required(VERSION 3.20)

project(windows_edr_lite C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(windows_edr_lite
    src/main.c
    src/logger.c
    include/logger.h
)

target_include_directories(windows_edr_lite PRIVATE
    include
)
