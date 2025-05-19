cmake_minimum_required(VERSION 3.30)
project(RabinVazirani)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(RabinVazirani main.cpp
        RabinVazirani.cpp
        RabinVazirani.h
        Graph.cpp
)

add_executable(rabin-vazirani-tests
        Graph.cpp
        RabinVazirani.cpp
        Test/GraphTest.cpp
        Test/RabinVaziraniTest.cpp
)

target_link_libraries(rabin-vazirani-tests
        PRIVATE
        GTest::GTest
        GTest::Main
)

target_include_directories(rabin-vazirani-tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)