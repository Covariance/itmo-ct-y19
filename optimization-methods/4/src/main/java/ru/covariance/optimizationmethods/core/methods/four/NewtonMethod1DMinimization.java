package ru.covariance.optimizationmethods.core.methods.four;

import ru.covariance.optimizationmethods.core.Matrix;
import ru.covariance.optimizationmethods.core.Point;
import ru.covariance.optimizationmethods.core.methods.one.GoldenRatioMinimizer;

import java.util.function.Function;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public class NewtonMethod1DMinimization extends AbstractMultidimMinimizer {
    Point pk;
    Point x1;
    double alpha;

    public NewtonMethod1DMinimization(ToDoubleFunction<Point> f, UnaryOperator<Point> grad, Function<Point, Matrix> gessian, Point x0) {
        super(f, grad, gessian, x0);
        x1 = x;
//        System.out.println("\\begin{tabular}{|c|c|c|c|}");
//        System.out.println("\\hline");
//        System.out.println("итерация & $|p_k|$ & $x_k$ & $\\alpha$ \\\\");
    }

    @Override
    public void iterate() {
        final Point g = grad.apply(x).multiply(-1);
        final Matrix H = gessian.apply(x);
        final Point p = ConjugateSolver.solveSOLE(H, g, epsilon);
        alpha = new GoldenRatioMinimizer(-100, 100, t -> f.applyAsDouble(x.add(p.multiply(t)))).getMin();
        x1 = x;
        x = x.add(p.multiply(alpha));
        pk = p;
    }

    private int iteration;

    @Override
    public void print() {
//        System.out.printf("B((%s), (%s), H)%n", x1.toString(), x.toString());
//        System.out.println("\\hline");
//        System.out.printf("$%d$ & $%.02f$ & $(%s)$ & $%.02e$ \\\\%n", ++iteration, pk.magnitude(), x.toString(), alpha);
    }

    @Override
    public boolean converged() {
        return pk != null && pk.magnitude() * Math.abs(alpha) < epsilon;
    }
}
