cmake_minimum_required(VERSION 3.10)
project(httpserver C CXX)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)
set(SOURCE_FILES
    src/server.cpp
    src/utils.c
)
add_executable(server ${SOURCE_FILES})
add_library(utils src/utils.c)
target_link_libraries(server PRIVATE utils)
include_directories(include/arpa)
find_package(Threads REQUIRED)
target_link_libraries(server PRIVATE Threads::Threads)
