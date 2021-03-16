package ru.covariance.optimizationmethods.core;

import java.util.List;
import java.util.function.DoubleFunction;

public abstract class AbstractIterativeMinimizer<T> extends AbstractMinimizer<T> {

  public AbstractIterativeMinimizer(List<T> borders, DoubleFunction<T> f) {
    super(borders, f);
  }

  public abstract void iterate();

  @Override
  public double min() {
    while (!this.converged()) {
      iterate();
    }
    return getMin();
  }
}
