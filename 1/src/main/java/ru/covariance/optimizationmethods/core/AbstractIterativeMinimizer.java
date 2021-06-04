package ru.covariance.optimizationmethods.core;

import java.util.List;
import java.util.function.ToDoubleFunction;

public abstract class AbstractIterativeMinimizer<T> extends AbstractMinimizer<T> {

  public AbstractIterativeMinimizer(List<T> borders, ToDoubleFunction<T> f) {
    super(borders, f);
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
