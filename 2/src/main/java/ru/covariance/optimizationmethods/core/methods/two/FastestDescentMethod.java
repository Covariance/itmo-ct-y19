package ru.covariance.optimizationmethods.core.methods.two;

import ru.covariance.optimizationmethods.core.AbstractFlatIterativeMinimizer;
import ru.covariance.optimizationmethods.core.Point;

import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public class FastestDescentMethod extends AbstractFlatIterativeMinimizer {
  private Point curPoint;
  private Point prevPoint;
  private Point curDirection;

  public FastestDescentMethod(Point left, Point right, ToDoubleFunction<Point> f, UnaryOperator<Point> gradient, double[] quadraticForm) {
    super(left, right, f, gradient, quadraticForm);
    prevPoint = curPoint = left.add(right).multiply(0.5);
    curDirection = gradient.apply(curPoint).multiply(-1);
  }

  @Override
  public void iterate() {
    prevPoint = curPoint;
    double alpha = MinimizerUtility.minimize(f, curPoint, curDirection, left, right);//curDirection.dotProduct(curDirection) / (MinimizerUtility.gesseMultiplication(curDirection, quadraticForm).dotProduct(curDirection));
    curPoint = curPoint.add(curDirection.multiply(alpha));
    curDirection = gradient.apply(curPoint).multiply(-1);
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
    return curDirection.magnitude() < epsilon;
  }
}
