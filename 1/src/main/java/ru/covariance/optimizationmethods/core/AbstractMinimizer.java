package ru.covariance.optimizationmethods.core;

import java.util.List;
import java.util.function.ToDoubleFunction;

public abstract class AbstractMinimizer<T> {
  protected final List<T> borders;
  protected final ToDoubleFunction<T> f;

  public AbstractMinimizer(final List<T> borders, ToDoubleFunction<T> f) {
    this.borders = borders;
    this.f = f;
  }

  public abstract T min();

  public abstract T getMin();

  public abstract boolean converged();

  public List<T> getBorders() {
    return borders;
  }
}
