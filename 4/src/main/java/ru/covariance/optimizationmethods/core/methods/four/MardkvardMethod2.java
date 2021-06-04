package ru.covariance.optimizationmethods.core.methods.four;

import ru.covariance.optimizationmethods.core.Matrix;
import ru.covariance.optimizationmethods.core.Point;

import java.util.function.Function;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public class MardkvardMethod2 extends AbstractMultidimMinimizer {
    Point x1;
    Point p;
    double tau;
    public static double beta = 0.5;

    public MardkvardMethod2(ToDoubleFunction<Point> f, UnaryOperator<Point> grad, Function<Point, Matrix> gessian, Point x0) {
        super(f, grad, gessian, x0);
        x1 = x;
        tau = 0;
    }

    private static boolean isPositive(Matrix a) {
        Matrix b = CholeskyDecomposition.decompose(a);
        if (b == null) {
            return false;
        }

        b = b.mul(b.transpose());
        for (int i = 0; i < a.getDim(); i++) {
            for (int j = 0; j < a.getDim(); j++) {
                if (Math.abs(a.get(i, j) - b.get(i, j)) > 1e-4) {
                    return false;
                }
            }
        }
        return true;
    }

    @Override
    public void iterate() {
        while (true) {
            if (!isPositive(gessian.apply(x).add(Matrix.E(x.getDim()).mul(tau)))) {
                tau = Math.max(1, 2 * tau);
                continue;
            }
            p = ConjugateSolver.solveSOLE(gessian.apply(x).add(Matrix.E(x.getDim()).mul(tau)), grad.apply(x).multiply(-1), epsilon);
            Point y = x.add(p);
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