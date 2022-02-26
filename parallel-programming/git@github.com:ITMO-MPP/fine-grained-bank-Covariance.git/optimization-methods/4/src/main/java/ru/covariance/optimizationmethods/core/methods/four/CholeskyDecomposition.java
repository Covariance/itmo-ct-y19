package ru.covariance.optimizationmethods.core.methods.four;

import ru.covariance.optimizationmethods.core.Matrix;

import static java.lang.Math.getExponent;
import static java.lang.Math.sqrt;

public class CholeskyDecomposition {
    public static boolean isSymmetric(double[][] A) {
        int N = A.length;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i; j++) {
                if (A[i][j] != A[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    // is symmetric
    public static boolean isSquare(double[][] A) {
        int N = A.length;
        for (int i = 0; i < N; i++) {
            if (A[i].length != N) {
                return false;
            }
        }
        return true;
    }


    // return Cholesky factor L of psd matrix A = L L^T
    public static double[][] cholesky(double[][] A) {
        if (!isSquare(A)) {
            return null;
        }
        if (!isSymmetric(A)) {
            return null;
        }

        int N = A.length;
        double[][] L = new double[N][N];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= i; j++) {
                double sum = 0.0;
                for (int k = 0; k < j; k++) {
                    sum += L[i][k] * L[j][k];
                }
                if (i == j) {
                    if (A[i][i] - sum < 0) {
                        return null;
                    }
                    L[i][i] = Math.sqrt(A[i][i] - sum);
                } else {
                    if (Math.abs(L[j][j]) < 1e-8) {
                        return null;
                    }
                    L[i][j] = 1.0 / L[j][j] * (A[i][j] - sum);
                }
            }
            if (L[i][i] <= 0) {
                return null;
            }
        }
        return L;
    }

    public static Matrix decompose(final Matrix a) {
        final double[][] b = cholesky(a.asArray());
        if (b == null) {
            return null;
        }
        Matrix c = new Matrix(a.getDim());
        for (int i = 0; i < a.getDim(); i++) {
            for (int j = 0; j < a.getDim(); j++) {
                c.set(i, j, b[i][j]);
            }
        }
        return c;
    }
}
