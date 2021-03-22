package ru.covariance.optimizationmethods.core.methods.two;

import javafx.geometry.Point2D;
import ru.covariance.optimizationmethods.core.AbstractFlatIterativeMinimizer;

import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public class ConjugateGradientMethod extends AbstractFlatIterativeMinimizer {
  private Point2D prevPoint;
  private Point2D curPoint;
  private Point2D curDirection;
  private final Point2D gesseRow1, gesseRow2;
  private final UnaryOperator<Point2D> gradient;
  private boolean firstIteration = true;

  public ConjugateGradientMethod(double leftX, double rightX, double leftY, double rightY, ToDoubleFunction<Point2D> f) {
    super(leftX, rightX, leftY, rightY, f);
    gradient = MathUtility2D.gradient(f);
    prevPoint = curPoint = new Point2D((leftX + rightX) / 2, (leftY + rightY) / 2);

    gesseRow1 = new Point2D(MathUtility2D.derivativeX(MathUtility2D.derivativeX(f), new Point2D(1, 1)),
        MathUtility2D.derivativeY(MathUtility2D.derivativeX(f), new Point2D(1, 1)));
    gesseRow2 = new Point2D(MathUtility2D.derivativeY(MathUtility2D.derivativeX(f), new Point2D(1, 1)),
        MathUtility2D.derivativeY(MathUtility2D.derivativeY(f), new Point2D(1, 1)));
  }

  @Override
  public void iterate() {
    firstIteration = false;
    double alpha = -gradient.apply(curPoint).dotProduct(curDirection) /
        curDirection.dotProduct(new Point2D(gesseRow1.dotProduct(curDirection),
            gesseRow2.dotProduct(curDirection)));
    Point2D newPoint = curPoint.add(curDirection.multiply(alpha));
    double omega = gradient.apply(newPoint).magnitude() / gradient.apply(curPoint).magnitude();

    prevPoint = curPoint;
    curPoint = newPoint;
    curDirection = gradient.apply(newPoint).multiply(-1).add(curDirection.multiply(omega));
  }

  @Override
  public Point2D getMin() {
    return curPoint;
  }

  @Override
  public boolean converged() {
    return !firstIteration && (curDirection.magnitude() < epsilon || prevPoint.distance(curPoint) < epsilon);
  }
}
