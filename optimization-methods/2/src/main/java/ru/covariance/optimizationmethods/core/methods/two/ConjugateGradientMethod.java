package ru.covariance.optimizationmethods.core.methods.two;

import ru.covariance.optimizationmethods.core.AbstractFlatIterativeMinimizer;
import ru.covariance.optimizationmethods.core.Point;

import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public class ConjugateGradientMethod extends AbstractFlatIterativeMinimizer {
  private Point prevPoint;
  private Point curPoint;
  private Point curDirection;
  private boolean firstIteration = true;
  private double prevGradientMagnitude;
  private Point prevGradient;

  public ConjugateGradientMethod(Point left, Point right, ToDoubleFunction<Point> f, UnaryOperator<Point> gradient, double[] quadraticForm) {
    super(left, right, f, gradient, quadraticForm);
    prevPoint = curPoint = left.add(right).multiply(0.5);
    curDirection = gradient.apply(curPoint).multiply(-1);
    prevGradientMagnitude = curDirection.dotProduct(curDirection);
    prevGradient = curDirection.multiply(-1);
  }

  @Override
  public void iterate() {
    firstIteration = false;
    final Point gessePoint = MinimizerUtility.gesseMultiplication(curDirection, quadraticForm);
    final double alpha = prevGradientMagnitude / curDirection.dotProduct(gessePoint);
    final Point newPoint = curPoint.add(curDirection.multiply(alpha));
    final Point newGradient = prevGradient.add(gessePoint.multiply(alpha));
    double curGradientMagnitude = newGradient.dotProduct(newGradient);
    final double beta = curGradientMagnitude / prevGradientMagnitude;

    prevPoint = curPoint;
    curPoint = newPoint;
    final Point prevDirection = curDirection;
    curDirection = newGradient.multiply(-1).add(curDirection.multiply(beta));
    prevGradientMagnitude = curGradientMagnitude;
    prevGradient = newGradient;
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
  public Point getDirection() {
    return curDirection;
  }

  @Override
  protected boolean resetDirections() {
    return false;
  }

  @Override
  public boolean converged() {
    return !firstIteration && (curDirection.magnitude() < epsilon || prevPoint.distance(curPoint) < epsilon);
  }
}
