package ru.covariance.optimizationmethods.core;

import javafx.geometry.Point2D;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Point {
  private final int dim;
  private final double[] coordinates;

  public Point(final Point other) {
    this.dim = other.dim;
    this.coordinates = other.coordinates;
  }

  public Point(double[] x) {
    coordinates = x;
    dim = x.length;
  }

  public Point(List<Double> x) {
    coordinates = new double[x.size()];
    dim = x.size();
    for (int i = 0; i < dim; i++) {
      coordinates[i] = x.get(i);
    }
  }

  public Point(Point2D x) {
    coordinates = new double[2];
    coordinates[0] = x.getX();
    coordinates[1] = x.getY();
    dim = 2;
  }

  public Point(double x, double y) {
    this(new Point2D(x, y));
  }

  public double getValue(int index) {
    return coordinates[index];
  }

  public void setValue(double value, int index) {
    coordinates[index] = value;
  }

  public int getDim() {
    return dim;
  }

  public Point multiply(double alpha) {
    Point result = new Point(new double[dim]);
    for (int i = 0; i < dim; i++) {
      result.setValue(coordinates[i] * alpha, i);
    }
    return result;
  }

  public Point add(Point other) {
    Point result = new Point(new double[dim]);
    for (int i = 0; i < dim; i++) {
      result.coordinates[i] = coordinates[i] + other.coordinates[i];
    }
    return result;
  }

  public Point subtract(Point other) {
    Point result = new Point(new double[dim]);
    for (int i = 0; i < dim; i++) {
      result.coordinates[i] = coordinates[i] - other.coordinates[i];
    }
    return result;
  }

  public double magnitude() {
    return Math.sqrt(dotProduct(this));
  }

  public double distance(final Point other) {
    return this.subtract(other).magnitude();
  }

  public double dotProduct(final Point other) {
    double dot = 0;
    for (int i = 0; i < dim; i++) {
      dot += coordinates[i] * other.coordinates[i];
    }
    return dot;
  }

  public double[] getCoordinates() {
    return coordinates;
  }

  public double getX() {
    return coordinates[0];
  }

  public double getY() {
    return coordinates[1];
  }

  @Override
  public String toString() {
    return Arrays.stream(coordinates).mapToObj(x -> String.format("%.2f", x)).collect(Collectors.joining(" "));
  }
}
