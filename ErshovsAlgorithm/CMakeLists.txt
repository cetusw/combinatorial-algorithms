cmake_minimum_required(VERSION 3.30)
project(ErshovsAlgorithm)

set(CMAKE_CXX_STANDARD 20)

add_executable(ErshovsAlgorithm main.cpp
        Graph/Graph.cpp
        Graph/Graph.h
        Vertex/Vertex.cpp
        Vertex/Vertex.h
        Edge/Edge.cpp
        Edge/Edge.h
        Face/Face.cpp
        Face/Face.h
        Consts.h
        Interface/IGraphElement.h)
