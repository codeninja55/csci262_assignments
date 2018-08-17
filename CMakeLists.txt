cmake_minimum_required(VERSION 3.10)
project(${PROJECT_SOURCE_DIR}/assignment01/ C)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/assignment01)

set(CMAKE_C_STANDARD 99)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/assignment01/")
set(SOURCE_FILES assignment01/md5.h assignment01/md5.c assignment01/Rainbow.c)

add_executable(Rainbow ${SOURCE_FILES})
