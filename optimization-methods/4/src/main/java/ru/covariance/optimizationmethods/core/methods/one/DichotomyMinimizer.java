package ru.covariance.optimizationmethods.core.methods.one;

import ru.covariance.optimizationmethods.core.AbstractMinimizer;

import java.util.function.DoubleUnaryOperator;

public class DichotomyMinimizer extends AbstractMinimizer {

    private final double delta;

    public DichotomyMinimizer(double left, double right, DoubleUnaryOperator f, double delta) {
        super(left, right, f);
        this.delta = delta;
    }

    @Override
    public void iterate() {
        double lp = (left + right - delta) / 2;
        double rp = (left + right + delta) / 2;
        if (f.applyAsDouble(lp) < f.applyAsDouble(rp)) {
            this.right = rp;
        } else {
            this.left = lp;
        }
    }

    @Override
    public Double getMin() {
        return (left + right) / 2;
    }

    @Override
    public boolean converged() {
        return right - left < 2 * delta;
    }
}
