cmake_minimum_required(VERSION 4.1)
project(windows_edr_lite C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(windows_edr_lite
        src/main.c
        src/process_monitor.c
        src/network_monitor.c
        src/detection_engine.c
        src/logger.c
        src/utils.c
        include/process_monitor.h
        include/detection_engine.h
        include/logger.h
        include/utils.h)
