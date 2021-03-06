package ru.covariance.optimizationmethods.core.methods.one;

import ru.covariance.optimizationmethods.core.AbstractMinimizer;

import java.util.function.DoubleUnaryOperator;

public class GoldenRatioMinimizer extends AbstractMinimizer {

    private final double RIGHT_TAU = (Math.sqrt(5) - 1) / 2;
    private final double LEFT_TAU = 1 - RIGHT_TAU;

    private double x1, x2;
    private double f_x1, f_x2;

    public GoldenRatioMinimizer(double left, double right, DoubleUnaryOperator f) {
        super(left, right, f);
        x1 = left + LEFT_TAU * (right - left);
        x2 = left + RIGHT_TAU * (right - left);
        f_x1 = f.applyAsDouble(x1);
        f_x2 = f.applyAsDouble(x2);
    }

    @Override
    public Double getMin() {
        while (!converged()) {
            iterate();
        }
        return x1;
    }

    @Override
    public boolean converged() {
        return Math.abs(f_x1 - f_x2) < epsilon;
    }

    @Override
    public void iterate() {
        if (f_x1 <= f_x2) {
            right = x2;
            x2 = x1;
            x1 = left + LEFT_TAU * (right - left);
            f_x2 = f_x1;
            f_x1 = f.applyAsDouble(x1);
        } else {
            left = x1;
            x1 = x2;
            x2 = left + RIGHT_TAU * (right - left);
            f_x1 = f_x2;
            f_x2 = f.applyAsDouble(x2);
        }
    }
}
