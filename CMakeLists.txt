cmake_minimum_required(VERSION 3.25.0)

set(CMAKE_CXX_STANDARD 17)

project(ray_trace_weekend)

add_executable(main src/main.cpp src/vec3.cpp src/ray3.cpp src/sphere.cpp src/hit.cpp src/util.cpp src/material.cpp)