//
// Created by covariance on 09.05.2021.
//

#include <iostream>
#include <gauss.h>
#include <generators.h>
#include <matrix.h>
#include <full_matrix.h>
#include <lu_decomposition.h>
#include <in_place_lu_decomposition.h>
#include <sole_solver_lu.h>
#include <skyline_matrix.h>
#include "profile_matrix.h"

int main() {
    std::vector<std::vector<long double>> data = {
            {1, 0, 3, 0},
            {0, 1, 1, 0},
            {2, 3, 8, 2},
            {0, 0, 2, 1}
    };
    std::vector<std::vector<long double>> l = {
        {},
        {},
        {3, 2},
        {2}
    };
    std::vector<std::vector<long double>> u = {
        {1},
        {1},
        {8, 1, 3},
        {1, 2}
    };
    auto a = skyline_matrix<long double>(u, l);
    auto lu = LUDecomposition(a);
    std::cout << lu.first << std::endl << lu.second << std::endl << mul(lu.first, lu.second) << std::endl;
    IPLUDecomposition(a);
    std::cout << a << std::endl;

    for (auto i : solve(a, {1, 1, 8, 1})) {
        std::cout << i << ' ';
    }

    std::cout << std::endl;

    for (auto i : solve(lu.first, lu.second, {1, 1, 8, 1})) {
        std::cout << i << ' ';
    }

    std::vector<std::vector<long double>> left = {
        {},
        {},
        {1},
        {},
        {2}
        },
        right = {
        {1},
        {1, 2},
        {1, 2, 3},
        {8},
        {1}
    };

    auto c = profile_matrix(5, left, right);

    auto newlu = LUDecomposition(c);

    std::cout << std::endl << c << std::endl << newlu.first << std::endl << newlu.second << std::endl << mul(newlu.first, newlu.second) << std::endl;

    IPLUDecomposition(c);
    for (auto i : solve(c, {1, 1, 1, 8, 1})) {
      std::cout << i << ' ';
    }

    return 0;
}