package ru.covariance.optimizationmethods.core.methods;

import ru.covariance.optimizationmethods.core.AbstractIterativeMinimizer;

import java.util.function.DoubleUnaryOperator;

public class DichotomyMinimizer extends AbstractIterativeMinimizer {

  private final double delta;

  public DichotomyMinimizer(double left, double right, DoubleUnaryOperator f, double delta) {
    super(left, right, f);
    this.delta = delta;
  }

  @Override
  public void iterate() {
    double lp = (left + right - delta) / 2;
    double rp = (left + right + delta) / 2;
    if (f.applyAsDouble(lp) < f.applyAsDouble(rp)) {
      this.right = rp;
    } else {
      this.left = lp;
    }
  }
}
