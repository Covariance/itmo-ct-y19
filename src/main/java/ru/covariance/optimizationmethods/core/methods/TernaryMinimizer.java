package ru.covariance.optimizationmethods.core.methods;

import java.util.function.DoubleUnaryOperator;
import ru.covariance.optimizationmethods.core.AbstractIterativeMinimizer;

public class TernaryMinimizer extends AbstractIterativeMinimizer {

  protected TernaryMinimizer(double left, double right, DoubleUnaryOperator f) {
    super(left, right, f);
  }

  @Override
  public void iterate() {
    double lp = (left * 2 + right) / 3;
    double rp = (left + right * 2) / 3;
    if (f.applyAsDouble(lp) < f.applyAsDouble(rp)) {
      this.right = rp;
    } else {
      this.left = lp;
    }
  }
}
