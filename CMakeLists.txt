cmake_minimum_required(VERSION 3.10)
project(httpserver C CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

set(SOURCE_FILES
    src/server.cpp
    src/utils.c
)

add_executable(server ${SOURCE_FILES})
add_library(utils src/utils.c)

target_link_libraries(server PRIVATE utils)
target_link_libraries(server PRIVATE pthread)
