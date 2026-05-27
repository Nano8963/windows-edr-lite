cmake_minimum_required(VERSION 3.20)

project(windows_edr_lite C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(windows_edr_lite
    src/main.c
    src/detection_engine.c
    src/logger.c
    src/process_monitor.c
    include/detection_engine.h
    include/logger.h
    include/process_monitor.h
)

target_include_directories(windows_edr_lite PRIVATE
    include
)
