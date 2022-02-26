package ru.covariance.optimizationmethods.core;

import java.util.function.Function;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public final class FunctionGeneratingData {
    private final ToDoubleFunction<Point> function;
    private final UnaryOperator<Point> gradient;
    private final Function<Point, Matrix> gessian;
    private final Point minPoint;

    public FunctionGeneratingData(ToDoubleFunction<Point> function, UnaryOperator<Point> gradient, Function<Point, Matrix> gessian) {
        this.function = function;
        this.gradient = gradient;
        this.gessian = gessian;
        minPoint = null;
    }

    public FunctionGeneratingData(ToDoubleFunction<Point> function, UnaryOperator<Point> gradient, Function<Point, Matrix> gessian, Point minPoint) {
        this.function = function;
        this.gradient = gradient;
        this.gessian = gessian;
        this.minPoint = minPoint;
    }

    public ToDoubleFunction<Point> getFunction() {
        return function;
    }

    public UnaryOperator<Point> getGradient() {
        return gradient;
    }

    public Function<Point, Matrix> getGessian() {
        return gessian;
    }

    public Point getMinPoint() {
        return minPoint;
    }
}
