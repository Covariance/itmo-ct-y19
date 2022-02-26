package ru.covariance.optimizationmethods.core;

import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public final class FunctionGeneratingData {
  private final ToDoubleFunction<Point> function;
  private final UnaryOperator<Point> gradient;
  private final double[] quadraticForm;
  private final Point minPoint;

  public FunctionGeneratingData(ToDoubleFunction<Point> function, UnaryOperator<Point> gradient, double[] quadraticForm) {
    this.function = function;
    this.gradient = gradient;
    this.quadraticForm = quadraticForm;
    minPoint = null;
  }

  public FunctionGeneratingData(ToDoubleFunction<Point> function, UnaryOperator<Point> gradient, double[] quadraticForm, Point minPoint) {
    this.function = function;
    this.gradient = gradient;
    this.quadraticForm = quadraticForm;
    this.minPoint = minPoint;
  }

  public ToDoubleFunction<Point> getFunction() {
    return function;
  }

  public UnaryOperator<Point> getGradient() {
    return gradient;
  }

  public double[] getQuadraticForm() {
    return quadraticForm;
  }

  public Point getMinPoint() {
    return minPoint;
  }
}
