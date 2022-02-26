package ru.covariance.optimizationmethods.core.methods.four;

import ru.covariance.optimizationmethods.core.Matrix;
import ru.covariance.optimizationmethods.core.Point;

import java.util.function.Function;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public class MardkvardMethod1 extends AbstractMultidimMinimizer {
    Point x1;
    Point p;
    double tau;
    public static double beta = 0.5;

    public MardkvardMethod1(ToDoubleFunction<Point> f, UnaryOperator<Point> grad, Function<Point, Matrix> gessian, Point x0) {
        super(f, grad, gessian, x0);
        x1 = x;
        tau = 100;
    }

    @Override
    public void iterate() {
        while (true) {
            p = ConjugateSolver.solveSOLE(gessian.apply(x).add(Matrix.E(x.getDim()).mul(tau)), grad.apply(x).multiply(-1), 1e-7);
            Point y = x.add(p);
            if (f.applyAsDouble(y) > f.applyAsDouble(x)) {
                tau /= beta;
                continue;
            }
            x1 = x;
            x = y;
            tau *= beta;
            break;
        }
    }

    @Override
    public void print() {
   }

    @Override
    public boolean converged() {
        return x.distance(x1) < epsilon;
    }
}