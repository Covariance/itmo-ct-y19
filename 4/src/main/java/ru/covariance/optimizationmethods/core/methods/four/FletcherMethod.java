package ru.covariance.optimizationmethods.core.methods.four;

import ru.covariance.optimizationmethods.core.Matrix;
import ru.covariance.optimizationmethods.core.Point;
import ru.covariance.optimizationmethods.core.methods.one.GoldenRatioMinimizer;

import java.util.function.Function;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public class FletcherMethod extends AbstractMultidimMinimizer {
    Matrix G;
    Point x1;
    double alpha;
    Point s;
    Point p;

    public FletcherMethod(ToDoubleFunction<Point> f, UnaryOperator<Point> grad, Function<Point, Matrix> gessian, Point x0) {
        super(f, grad, gessian, x0);
        G = new Matrix(x0.getDim());
        for (int i = 0; i < x0.getDim(); i++) {
            G.set(i, i, 1);
        }
        x1 = x;
//        System.out.println("\\begin{tabular}{|c|c|c|}");
//        System.out.println("\\hline");
//        System.out.println("номер итерации & $|s_k|$ & $x_k$ \\\\");
    }

    @Override
    public void iterate() {
        final Point g = grad.apply(x).multiply(-1);
//        if (true || iteration != 0) {
            p = G.multiply(g);
            alpha = new GoldenRatioMinimizer(-10, 10, t -> f.applyAsDouble(x.add(p.multiply(t)))).getMin();
            s = p.multiply(alpha);
            x1 = x;
            x = x.add(s);

            Point y = grad.apply(x).subtract(grad.apply(x1));
            double sy = s.dotProduct(y);
            double t1 = (sy + y.dotProduct(G.multiply(y))) / Math.pow(sy, 2);
            G = G.add(s.mul(s).mul(t1))
                 .sub(G.mul(y.mul(s)).add(s.mul(y).mul(G)).mul(1 / sy));
//        } else {
//            alpha = new GoldenRatioMinimizer(-100, 100, t -> f.applyAsDouble(x.add(g.multiply(t)))).getMin();
//            x1 = x;
//            x = x.add(g.multiply(alpha));
//            p = g.multiply(alpha);
//        }
//        ++iteration;
    }

    private int iteration;

    @Override
    public void print() {
//        System.out.printf("B((%s), (%s), H)%n", x1.toString(), x.toString());
//        System.out.printf("$%d$ & $%.02f$ & $(%s)$ \\\\%n", ++iteration, s.magnitude(), x.toString());
    }

    @Override
    public boolean converged() {
        return p.magnitude() < epsilon;
    }
}
