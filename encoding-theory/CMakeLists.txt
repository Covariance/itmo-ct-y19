cmake_minimum_required(VERSION 3.22)
project(encoding_theory)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DLOCAL -DDEBUG -DNO_SPEED)

add_executable(A A.cpp)
add_executable(J J.cpp)