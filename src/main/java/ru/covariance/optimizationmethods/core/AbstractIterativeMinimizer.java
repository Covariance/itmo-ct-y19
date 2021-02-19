package ru.covariance.optimizationmethods.core;

import java.util.function.DoubleUnaryOperator;

public abstract class AbstractIterativeMinimizer extends AbstractMinimizer {

  public static final double EPSILON = 1e-9;

  protected AbstractIterativeMinimizer(double left, double right, DoubleUnaryOperator f) {
    super(left, right, f);
  }

  public abstract void iterate();

  @Override
  public double min() {
    while (right - left > EPSILON) {
      System.out.println(left + " " + right);
      iterate();
    }
    return left + (right - left) / 2;
  }
}
