package ru.covariance.optimizationmethods.core;

import java.util.function.DoubleUnaryOperator;

public abstract class AbstractMinimizer {

  public static final double EPSILON = 1e-9;

  protected double left;
  protected double right;

  protected final DoubleUnaryOperator f;

  public AbstractMinimizer(double left, double right, DoubleUnaryOperator f) {
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

  public boolean converged() {
    return left - right < EPSILON;
  }
}
