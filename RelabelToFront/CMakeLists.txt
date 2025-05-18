cmake_minimum_required(VERSION 3.30)
project(RelabelToFront)

set(CMAKE_CXX_STANDARD 20)

add_executable(RelabelToFront main.cpp
        Network.cpp
        Network.h
        RelabelToFront.cpp
        RelabelToFront.h)
