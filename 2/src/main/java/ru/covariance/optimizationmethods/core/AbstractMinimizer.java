package ru.covariance.optimizationmethods.core;

import java.util.function.ToDoubleFunction;

public abstract class AbstractMinimizer<T> {
  protected final ToDoubleFunction<T> f;

  public AbstractMinimizer(ToDoubleFunction<T> f) {
    this.f = f;
  }

  public abstract T min();

  public abstract T getMin();

  public abstract boolean converged();
}
