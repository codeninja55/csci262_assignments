cmake_minimum_required(VERSION 3.10)
project(${PROJECT_SOURCE_DIR}/assignment01/ C)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/assignment01)
include_directories(/usr/include/)
include_directories(/usr/include/openssl/)

link_libraries(crypto)
link_libraries(m)

set(CMAKE_C_STANDARD 99)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lssl -lcrypto -lm")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/assignment01/")
#set(SOURCE_FILES assignment01/md5.h assignment01/md5.c assignment01/helper.c
#        assignment01/avltree.h assignment01/avltree.c assignment01/Rainbow.c)
set(SOURCE_FILES assignment01/helper.h assignment01/helper.c
        assignment01/avltree.h assignment01/avltree.c
        assignment01/Rainbow.c)

add_executable(Rainbow ${SOURCE_FILES})
