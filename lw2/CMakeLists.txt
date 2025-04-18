cmake_minimum_required(VERSION 3.30)
project(lw2)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(lw2 Matrix.cpp Graph.cpp main.cpp)
add_executable(graph-tests Matrix.cpp Graph.cpp tests/GraphTests.cpp)

target_link_libraries(graph-tests PRIVATE Catch2::Catch2WithMain)
