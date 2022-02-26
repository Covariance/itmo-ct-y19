package ru.covariance.optimizationmethods.core.methods.two;

import ru.covariance.optimizationmethods.core.AbstractFlatIterativeMinimizer;
import ru.covariance.optimizationmethods.core.AbstractIterativeMinimizer;
import ru.covariance.optimizationmethods.core.Point;

import java.util.Arrays;
import java.util.Collections;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public class GradientMethod extends AbstractFlatIterativeMinimizer {
  private Point prevPoint;
  private Point curPoint;
  public double alpha;

  public GradientMethod(Point left, Point right, ToDoubleFunction<Point> f, UnaryOperator<Point> gradient, double[] quadraticForm) {
    super(left, right, f, gradient, quadraticForm);
    prevPoint = curPoint = left.add(right).multiply(0.5);
    alpha = 1.0 / (Arrays.stream(quadraticForm).max().getAsDouble() * 2.0);
  }

  @Override
  public void iterate() {
    prevPoint = curPoint;
    final Point curDirection = gradient.apply(curPoint);
    final Point newPoint = curPoint.add(curDirection.multiply(-alpha));
    if (f.applyAsDouble(newPoint) < f.applyAsDouble(curPoint)) {
      curPoint = newPoint;
    } else {
      alpha /= 2;
      if (alpha < 1e-12) {
        alpha = 1;
      }
    }
//    System.err.printf("%.08f%n", curDirection.magnitude());
    super.iterate();
  }

  @Override
  public Point getCurrentPoint() {
    return curPoint;
  }

  @Override
  public Point getPreviousPoint() {
    return prevPoint;
  }

  @Override
  public Point getMin() {
    return curPoint;
  }

  @Override
  public boolean converged() {
    return gradient.apply(curPoint).magnitude() < epsilon;
  }
}
