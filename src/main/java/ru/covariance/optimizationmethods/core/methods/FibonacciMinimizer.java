package ru.covariance.optimizationmethods.core.methods;

import ru.covariance.optimizationmethods.core.AbstractDoubleIterativeMinimizer;

import java.util.function.DoubleUnaryOperator;

public class FibonacciMinimizer extends AbstractDoubleIterativeMinimizer {

  private final double F_n2;
  private final double left_0;
  private final double right_0;

  private double F_nk1, F_nk2;
  private double x1, x2;
  private double f_x1, f_x2;

  public FibonacciMinimizer(double left, double right, DoubleUnaryOperator f) {
    super(left, right, f);
    double a = 1;
    double b = 1;
    while ((right - left) > (a + b) * epsilon) {
      double c = b;
      b = a + b;
      a = c;
    }
    F_n2 = a + b;
    F_nk1 = b;
    F_nk2 = a;

    left_0 = left;
    right_0 = right;

    x1 = left + F_nk2 / F_n2 * (right_0 - left_0);
    x2 = left + F_nk1 / F_n2 * (right_0 - left_0);
    f_x1 = f.applyAsDouble(x1);
    f_x2 = f.applyAsDouble(x2);
  }

  @Override
  public void iterate() {
    double F_nk3 = F_nk1 - F_nk2;
    F_nk1 = F_nk2;
    F_nk2 = F_nk3;
    if (f_x1 <= f_x2) {
      right = x2;
      x2 = x1;
      x1 = left + F_nk2 / F_n2 * (right_0 - left_0);
      f_x2 = f_x1;
      f_x1 = f.apply(x1);
    } else {
      left = x1;
      x1 = x2;
      x2 = left + F_nk1 / F_n2 * (right_0 - left_0);
      f_x1 = f_x2;
      f_x2 = f.apply(x2);
    }
  }
}
