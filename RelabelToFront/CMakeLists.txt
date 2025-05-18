cmake_minimum_required(VERSION 3.30)
project(RelabelToFront)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(RelabelToFront main.cpp
        Network.cpp
        Network.h
        RelabelToFront.cpp
        RelabelToFront.h
)

add_executable(relabel-to-front-tests
        Network.cpp
        Network.h
        RelabelToFront.cpp
        RelabelToFront.h
        Test/RelabelToFrontTest.cpp
)

target_link_libraries(relabel-to-front-tests
        PRIVATE
        GTest::GTest
        GTest::Main
)

target_include_directories(relabel-to-front-tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
