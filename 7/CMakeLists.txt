cmake_minimum_required(VERSION 3.17)
project(7)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(DEBUG)

add_executable(A A.cpp)
add_executable(B B.cpp)
add_executable(C C.cpp)
add_executable(D D.cpp)
add_executable(E E.cpp)