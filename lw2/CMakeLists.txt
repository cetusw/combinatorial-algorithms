cmake_minimum_required(VERSION 3.30)
project(lw2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lw2 main.cpp
        Graph.cpp
        Graph.h
        Types.h
)
