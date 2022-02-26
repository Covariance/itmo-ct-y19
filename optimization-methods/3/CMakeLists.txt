cmake_minimum_required(VERSION 3.17)
project(sole_solver CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
#set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -fno-sanitize-recover")

add_executable(sole_solver
        matrix.h
        full_matrix.h
        main.cpp
        lu_decomposition.h
        full_matrix.h
        left_triangle_matrix.h
        right_triangle_matrix.h
        in_place_lu_decomposition.h
        gauss.h
        generators.h
        sparse_matrix.h
        skyline_matrix.h
        sole_solver_lu.h
        conjugate.h)


add_executable(tests
        matrix.h
        full_matrix.h
        sparse_matrix.h
        generators.h
        tests.cpp)

add_executable(benchmarks
        matrix.h
        sparse_matrix.h
        full_matrix.h
        conjugate.h
        gauss.h
        generators.h
        benchmark.cpp profile_matrix.h)