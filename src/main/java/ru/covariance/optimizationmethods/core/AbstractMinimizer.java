package ru.covariance.optimizationmethods.core;

import java.util.List;
import java.util.function.DoubleFunction;

public abstract class AbstractMinimizer<T> {
  protected final List<T> borders;
  protected final DoubleFunction<T> f;

  public AbstractMinimizer(final List<T> borders, DoubleFunction<T> f) {
    this.borders = borders;
    this.f = f;
  }

  public abstract double min();

  public abstract double getMin();

  public abstract boolean converged();

  public List<T> getBorders() {
    return borders;
  }
}
