package ru.covariance.optimizationmethods.core.methods.one;

import ru.covariance.optimizationmethods.core.AbstractMinimizer;

import java.util.function.DoubleUnaryOperator;

public class ParabolicMinimizer extends AbstractMinimizer {

  private static final double DEFAULT_DELTA = 1e-6;

  private double mid;
  private final double delta;
  private boolean converged;

  private double fleft;
  private double fmid;
  private double fright;

  public ParabolicMinimizer(double left, double right, DoubleUnaryOperator f, double delta) {
    super(left, right, f);
    this.mid = (left + right) / 2;
    this.delta = delta;
    this.converged = false;

    this.fleft = f.applyAsDouble(left);
    this.fmid = f.applyAsDouble(mid);
    this.fright = f.applyAsDouble(right);
  }

  public ParabolicMinimizer(double left, double right, DoubleUnaryOperator f) {
    this(left, right, f, DEFAULT_DELTA);
  }

  @Override
  public void iterate() {
    double xopt = mid - ((mid - left) * (mid - left) * (fmid - fright) - (mid - right)
        * (mid - right) * (fmid - fleft)) / (2 * ((mid - left) * (fmid - fright) - (mid - right)
        * (fmid - fleft)));

    if (Math.abs(xopt - mid) < delta) {
      converged = true;
    }

    double fxopt = f.applyAsDouble(xopt);

    if (xopt < mid) {
      if (fxopt < fmid) {
        fright = fmid;
        right = mid;

        fmid = fxopt;
        mid = xopt;
      } else {
        fleft = fxopt;
        left = xopt;
      }
    } else {
      if (fxopt < fmid) {
        fleft = fmid;
        left = mid;

        fmid = fxopt;
        mid = xopt;
      } else {
        fright = fxopt;
        right = xopt;
      }
    }

    if (mid == left || mid == right) {
      converged = true;
    }
  }

  @Override
  public boolean converged() {
    return converged;
  }

  @Override
  public Double getMin() {
    return mid;
  }
}
