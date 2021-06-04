package ru.covariance.optimizationmethods.core.methods.two;

import javafx.geometry.Point2D;

import java.util.function.DoubleBinaryOperator;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public class MathUtility2D {
    private static final double h = 1e-8;

    public static Point2D gradient(ToDoubleFunction<Point2D> function, Point2D point) {
        return new Point2D(derivativeX(function, point), derivativeY(function, point));
    }

    public static UnaryOperator<Point2D> gradient(ToDoubleFunction<Point2D> function) {
        return point -> new Point2D(derivativeX(function, point), derivativeY(function, point));
    }

    public static double derivativeX(ToDoubleFunction<Point2D> function, Point2D point) {
        return (function.applyAsDouble(new Point2D(point.getX() + h, point.getY() + h)) -
                function.applyAsDouble(new Point2D(point.getX(), point.getY()))) / (2 * h);
    }

    public static ToDoubleFunction<Point2D> derivativeX(ToDoubleFunction<Point2D> function) {
        return point -> (function.applyAsDouble(new Point2D(point.getX() + h, point.getY() + h)) -
                function.applyAsDouble(new Point2D(point.getX(), point.getY()))) / (2 * h);
    }

    public static double derivativeY(ToDoubleFunction<Point2D> function, Point2D point) {
        return (function.applyAsDouble(new Point2D(point.getX(), point.getY())) -
                function.applyAsDouble(new Point2D(point.getX() + h, point.getY() - h))) / (2 * h);
    }

    public static ToDoubleFunction<Point2D> derivativeY(ToDoubleFunction<Point2D> function) {
        return point -> (function.applyAsDouble(new Point2D(point.getX(), point.getY())) -
                function.applyAsDouble(new Point2D(point.getX() + h, point.getY() - h))) / (2 * h);
    }

    public static double derivative(ToDoubleFunction<Point2D> function, Point2D point) {
        return (function.applyAsDouble(new Point2D(point.getX() + h, point.getY() + h)) -
                function.applyAsDouble(new Point2D(point.getX() - h, point.getY() - h))) / (2 * h);
    }

    public static ToDoubleFunction<Point2D> derivative(ToDoubleFunction<Point2D> function) {
        return point -> (function.applyAsDouble(new Point2D(point.getX() + h, point.getY() + h)) -
                function.applyAsDouble(new Point2D(point.getX() - h, point.getY() - h))) / (2 * h);
    }
}
