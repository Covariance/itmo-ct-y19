package ru.covariance.optimizationmethods.core.methods.four;

import ru.covariance.optimizationmethods.core.Matrix;
import ru.covariance.optimizationmethods.core.Point;

import java.util.function.Function;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public class NewtonMethod extends AbstractMultidimMinimizer {
    Point pk;
    Point x1;

    public NewtonMethod(ToDoubleFunction<Point> f, UnaryOperator<Point> grad, Function<Point, Matrix> gessian, Point x0) {
        super(f, grad, gessian, x0);
        x1 = x;
//        System.out.println("\\begin{tabular}{|c|c|c|}");
//        System.out.println("\\hline");
//        System.out.println("номер итерации & $|p_k|$ & $x_k$ \\\\");
    }

    @Override
    public void iterate() {
        final Point g = grad.apply(x).multiply(-1);
        final Matrix H = gessian.apply(x);
        final Point p = ConjugateSolver.solveSOLE(H, g, epsilon);
        x1 = x;
        x = x.add(p);
        pk = p;
    }

    private int iteration;

    @Override
    public void print() {
        System.out.printf("B((%s), (%s), H)%n", x1.toString(), x.toString());
//        System.out.println("\\hline");
//        System.out.printf("$%d$ & $%.02f$ & $(%s)$ \\\\%n", ++iteration, pk.magnitude(), x.toString());
    }

    @Override
    public boolean converged() {
        return pk != null && pk.magnitude() < epsilon;
    }
}
