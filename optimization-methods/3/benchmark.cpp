//
// Created by stepavly on 13.05.2021.
//

#include "full_matrix.h"
#include "sparse_matrix.h"
#include "generators.h"
#include "gauss.h"
#include <iostream>
#include <chrono>
#include "in_place_lu_decomposition.h"
#include "sole_solver_lu.h"
#include "lu_decomposition.h"
using namespace std;

template<typename T>
ostream &print(const vector<T> &a) {
  if (a.empty()) {
    cout << "[]";
    return cout;
  }
  cout << "[" << a[0];
  for (uint32_t i = 1; i < a.size(); i++) {
    cout << ", " << a[i];
  }
  cout << "]";
  return cout;
}

int main() {
  cout.precision(12);
  cout << fixed;

  if (true) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    cout << "LU-DECOMPOSITION ON USUAL MATRIX" << endl;
    for (int n : {500}) {
      cout << "\\begin{tabular}{|c|c|c|c|}" << endl;
      cout << "\\hline" << endl;
      cout << "$n$ & $k$ & || $x^* - x_k$ || & $\\frac{|| x^* - x_k ||}{||x^*||}$ \\\\" << endl;
      cout << "\\hline" << endl;
      for (int k = 0; k <= 0; k++) {
        auto[A, f, b] = genFull(n, n, pow(10, -k));
//        IPLUDecomposition(A);
        auto[l, u] = LUDecomposition(A);
        vector<ld> x = solve(l, u, b);
//        vector<ld> x = solve(A, b);
        ld distXF = magnitude(sub(x, f));
        cout << "$" << n << "$ & $" << k << "$ & $" << distXF << "$ & $" << distXF / magnitude(f) << "$ \\\\ "
             << endl;
        cout << "\\hline" << endl;
      }
      cout << "\\end{tabular}" << endl;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
  }

  if (false) {
    cout << "LU-DECOMPOSITION ON HILBERT MATRIX" << endl;
    cout << "\\begin{tabular}{|c|c|c|}" << endl;
    cout << "\\hline" << endl;
    cout << "$n$ & || $x^* - x_k$ || & $\\frac{|| x^* - x_k ||}{||x^*||}$ \\\\" << endl;
    cout << "\\hline" << endl;
    for (int n : {100}) {
      auto[A, f, b] = genHilbert(n);
      auto[l, u] = LUDecomposition(A);
      cout << l << endl << u << endl;
//      IPLUDecomposition(A);
      vector<ld> x = solve(l, u, b);
      ld distXF = magnitude(sub(x, f));
      cout << "$" << n << "$ & $" << distXF << "$ & $" << distXF / magnitude(f) << "$ \\\\ " << endl;
      cout << "\\hline" << endl;
    }
    cout << "\\end{tabular}" << endl;
  }

  if (true) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    cout << "GAUSS ELIMINATION" << endl;
    for (int n : {500}) {
      cout << "\\begin{tabular}{|c|c|c|c|}" << endl;
      cout << "\\hline" << endl;
      cout << "$n$ & $k$ & || $x^* - x_k$ || & $\\frac{|| x^* - x_k ||}{||x^*||}$ \\\\" << endl;
      cout << "\\hline" << endl;
      for (int k = 0; k <= 0; k++) {
        auto[A, f, b] = genFull(n, n, pow(10, -k));
        vector<ld> x(n);
        if (gauss(A, b, x) == -1) {
          continue;
        }
        ld distXF = magnitude(sub(x, f)); // |x-f|/|f|
        cout << "$" << n << "$ & $" << k << "$ & $" << distXF << "$ & $" << distXF / magnitude(f) << "$ \\\\ " << endl;
        cout << "\\hline" << endl;
      }
      cout << "\\end{tabular}" << endl;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    return 0;
  }

  if (true) {
    cout << "GAUSS ELIMINATION ON HILBERT MATRIX" << endl;
    cout << "\\begin{tabular}{|c|c|c|}" << endl;
    cout << "\\hline" << endl;
    cout << "$n$ & || $x^* - x_k$ || & $\\frac{|| x^* - x_k ||}{||x^*||}$ \\\\" << endl;
    cout << "\\hline" << endl;
    for (int n : {1, 5, 10, 25, 50, 75, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}) {
      auto[A, f, b] = genHilbert(n);
      vector<ld> x(n);
      if (gauss(A, b, x) == -1) {
        continue;
      }
      ld distXF = magnitude(sub(x, f)); // |x-f|/|f|
      cout << "$" << n << "$ & $" << distXF << "$ & $" << distXF / magnitude(f) << "$ \\\\ " << endl;
      cout << "\\hline" << endl;
    }
    cout << "\\end{tabular}" << endl;
  }

  if (true) {
    cout << "GAUSS ELIMINATION" << endl;
    for (int n : {10, 100, 500}) {
      cout << "\\begin{tabular}{|c|c|c|c|}" << endl;
      cout << "\\hline" << endl;
      cout << "$n$ & $k$ & || $x^* - x_k$ || & $\\frac{|| x^* - x_k ||}{||x^*||}$ \\\\" << endl;
      cout << "\\hline" << endl;
      for (int k = 0; k <= 8; k++) {
        auto[A, f, b] = genFull(n, n, pow(10, -k));
        vector<ld> x(n);
        if (gauss(A, b, x) == -1) {
          continue;
        }
        ld distXF = magnitude(sub(x, f)); // |x-f|/|f|
        cout << "$" << n << "$ & $" << k << "$ & $" << distXF << "$ & $" << distXF / magnitude(f) << "$ \\\\ " << endl;
        cout << "\\hline" << endl;
      }
      cout << "\\end{tabular}" << endl;
    }
  }

  if (true) {
    cout << "GAUSS ELIMINATION ON HILBERT MATRIX" << endl;
    cout << "\\begin{tabular}{|c|c|c|}" << endl;
    cout << "\\hline" << endl;
    cout << "$n$ & || $x^* - x_k$ || & $\\frac{|| x^* - x_k ||}{||x^*||}$ \\\\" << endl;
    cout << "\\hline" << endl;
    for (int n : {1, 5, 10, 25, 50, 75, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}) {
      auto[A, f, b] = genHilbert(n);
      vector<ld> x(n);
      if (gauss(A, b, x) == -1) {
        continue;
      }
      ld distXF = magnitude(sub(x, f)); // |x-f|/|f|
      cout << "$" << n << "$ & $" << distXF << "$ & $" << distXF / magnitude(f) << "$ \\\\ " << endl;
    }
    cout << "\\end{tabular}" << endl;
  }
}