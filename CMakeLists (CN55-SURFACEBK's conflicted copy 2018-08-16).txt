cmake_minimum_required(VERSION 3.10)
project(${PROJECT_SOURCE_DIR}/assignment01/ C)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/assignment01)

set(CMAKE_C_STANDARD 99)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/assignment01/")

add_executable(Rainbow assignment01/Rainbow.c)
