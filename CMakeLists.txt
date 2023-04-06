cmake_minimum_required(VERSION 3.25.0)

set(CMAKE_CXX_STANDARD 17)

project(ray_trace_weekend)

FILE(GLOB SRC src/*.cpp)

add_executable(main ${SRC})