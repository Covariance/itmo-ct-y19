package ru.covariance.optimizationmethods.core;

import java.util.function.DoubleUnaryOperator;

public abstract class AbstractMinimizer {

  protected double left;
  protected double right;

  protected final DoubleUnaryOperator f;

  protected AbstractMinimizer(double left, double right, DoubleUnaryOperator f) {
    this.left = left;
    this.right = right;
    this.f = f;
  }

  public abstract double min();

  public double getLeft() {
    return left;
  }

  public double getRight() {
    return right;
  }
}
