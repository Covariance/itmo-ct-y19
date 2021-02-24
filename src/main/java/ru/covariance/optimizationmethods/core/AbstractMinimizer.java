package ru.covariance.optimizationmethods.core;

import java.util.function.DoubleUnaryOperator;

public abstract class AbstractMinimizer {
  protected double epsilon = 1e-6;

  protected double left;
  protected double right;

  protected final DoubleUnaryOperator f;

  public AbstractMinimizer(double left, double right, DoubleUnaryOperator f) {
    this.left = left;
    this.right = right;
    this.f = f;
  }

  public abstract double min();

  public abstract double getMin();

  public double getLeft() {
    return left;
  }

  public double getRight() {
    return right;
  }

  public double getEpsilon() {
    return epsilon;
  }

  public void setEpsilon(double epsilon) {
    this.epsilon = epsilon;
  }

  public boolean converged() {
    return right - left < epsilon;
  }
}
