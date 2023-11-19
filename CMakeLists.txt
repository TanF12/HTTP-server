cmake_minimum_required(VERSION 3.10)
project(MixedLangProject C CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(server server.cpp)

add_library(utils utils.c)

target_link_libraries(server PRIVATE utils)
target_link_libraries(server PRIVATE pthread)
