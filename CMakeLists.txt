cmake_minimum_required(VERSION 3.17)
project(cache_oblivious)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB SRC src/*.cpp)

add_executable(cache_oblivious ${SRC})
