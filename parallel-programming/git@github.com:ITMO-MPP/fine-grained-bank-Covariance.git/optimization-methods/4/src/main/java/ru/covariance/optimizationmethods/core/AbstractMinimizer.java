package ru.covariance.optimizationmethods.core;

import java.util.function.DoubleUnaryOperator;

public abstract class AbstractMinimizer {
    public static double epsilon = 1e-8;
    public double left, right;
    public DoubleUnaryOperator f;

    protected AbstractMinimizer(double left, double right, DoubleUnaryOperator f) {
        this.left = left;
        this.right = right;
        this.f = f;
    }

    public abstract Double getMin();

    public abstract boolean converged();

    public abstract void iterate();
}
