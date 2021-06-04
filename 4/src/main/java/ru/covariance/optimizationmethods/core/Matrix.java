package ru.covariance.optimizationmethods.core;

public final class Matrix {
    private final Point[] rows;

    public Matrix(int dim) {
        rows = new Point[dim];
        for (int i = 0; i < dim; i++) {
            rows[i] = new Point(new double[dim]);
        }
    }

    public Matrix(final Point... points) {
        rows = points;
    }

    public void set(int i, int j, double value) {
        rows[i].set(value, j);
    }

    public Point multiply(final Point other) {
        final Point res = new Point(new double[rows.length]);
        for (int i = 0; i < rows.length; i++) {
            res.set(other.dotProduct(rows[i]), i);
        }
        return res;
    }

    public int getDim() {
        return rows.length;
    }

    public double get(int i, int j) {
        return rows[i].get(j);
    }

    public Matrix add(Matrix b) {
        Matrix a = this;
        Matrix c = new Matrix(a.getDim());
        for (int i = 0; i < a.getDim(); i++) {
            for (int j = 0; j < a.getDim(); j++) {
                c.set(i, j, a.get(i, j) + b.get(i, j));
            }
        }
        return c;
    }

    public Matrix sub(Matrix b) {
        Matrix a = this;
        Matrix c = new Matrix(a.getDim());
        for (int i = 0; i < a.getDim(); i++) {
            for (int j = 0; j < a.getDim(); j++) {
                c.set(i, j, a.get(i, j) - b.get(i, j));
            }
        }
        return c;
    }

    public Matrix mul(double b) {
        Matrix a = this;
        Matrix c = new Matrix(a.getDim());
        for (int i = 0; i < a.getDim(); i++) {
            for (int j = 0; j < a.getDim(); j++) {
                c.set(i, j, a.get(i, j) * b);
            }
        }
        return c;
    }

    public Matrix mul(Matrix b) {
        Matrix c = new Matrix(getDim());
        for (int i = 0; i < getDim(); i++) {
            for (int j = 0; j < getDim(); j++) {
                for (int k = 0; k < getDim(); k++) {
                    c.set(i, j, c.get(i, j) + get(i, k) * b.get(k, j));
                }
            }
        }
        return c;
    }

    public static Matrix E(int n) {
        Matrix a = new Matrix(n);
        for (int i = 0; i < n; i++) {
            a.set(i, i, 1);
        }
        return a;
    }

    public double[][] asArray() {
        double[][] a = new double[getDim()][getDim()];
        for (int i = 0; i < getDim(); i++) {
            for (int j = 0; j < getDim(); j++) {
                a[i][j] = get(i, j);
            }
        }
        return a;
    }

    public Matrix transpose() {
        Matrix a = new Matrix(getDim());
        for (int i = 0; i < getDim(); i++) {
            for (int j = 0; j < getDim(); j++) {
//                a.set(j, getDim() - i - 1, get(i, j));
                a.set(j, i, get(i, j));
            }
        }
        return a;
    }
}
