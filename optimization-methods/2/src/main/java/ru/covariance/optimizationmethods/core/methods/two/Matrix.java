package ru.covariance.optimizationmethods.core.methods.two;

import ru.covariance.optimizationmethods.core.Point;

public class Matrix {
  private final Point[] rows;

  public Matrix(int dim) {
    rows = new Point[dim];
    for (int i = 0; i < dim; i++) {
      rows[i] = new Point(new double[dim]);
    }
  }

  public void set(int i, int j, double value) {
    rows[i].setValue(value, j);
  }

  public Point multiply(final Point other) {
    final Point res = new Point(new double[rows.length]);
    for (int i = 0; i < rows.length; i++) {
      res.setValue(other.dotProduct(rows[i]), i);
    }
    return res;
  }
}
