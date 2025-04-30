cmake_minimum_required(VERSION 3.30)
project(ErshovsAlgorithm)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_library(graphlib
        Graph/Graph.cpp
        Vertex/Vertex.cpp
        Edge/Edge.cpp
        Face/Face.cpp
)

target_include_directories(graphlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ErshovsAlgorithm main.cpp)
target_link_libraries(ErshovsAlgorithm PRIVATE graphlib)

add_executable(ershov-tests Test/ErshovAlgorithmTest.cpp)

target_link_libraries(ershov-tests
        PRIVATE
        GTest::GTest
        GTest::Main
        graphlib
)
