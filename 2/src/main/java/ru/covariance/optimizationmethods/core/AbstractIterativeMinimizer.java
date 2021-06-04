package ru.covariance.optimizationmethods.core;

import java.util.function.ToDoubleFunction;

public abstract class AbstractIterativeMinimizer<T> extends AbstractMinimizer<T> {

  public AbstractIterativeMinimizer(ToDoubleFunction<T> f) {
    super(f);
  }

  public abstract void iterate();

  @Override
  public T min() {
    while (!this.converged()) {
      iterate();
    }
    return getMin();
  }
}
