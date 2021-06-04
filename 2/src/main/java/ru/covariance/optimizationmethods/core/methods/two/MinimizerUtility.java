package ru.covariance.optimizationmethods.core.methods.two;

import ru.covariance.optimizationmethods.core.methods.one.*;
import ru.covariance.optimizationmethods.core.Point;

import java.util.function.ToDoubleFunction;

public class MinimizerUtility {
  public static Point gesseMultiplication(final Point point, final double[] quadraticForm) {
    final double[] coord = new double[point.getDim()];
    for (int i = 0; i < point.getDim(); i++) {
      coord[i] = point.getValue(i) * quadraticForm[i];
    }
    return new Point(coord);
  }

  public static double minimize(final ToDoubleFunction<Point> f, final Point point, final Point direction, final Point leftDown, final Point rightUpper) {
    return new FibonacciMinimizer(0, leftDown.distance(rightUpper), t -> f.applyAsDouble(point.add(direction.multiply(t)))).min();
  }
}
