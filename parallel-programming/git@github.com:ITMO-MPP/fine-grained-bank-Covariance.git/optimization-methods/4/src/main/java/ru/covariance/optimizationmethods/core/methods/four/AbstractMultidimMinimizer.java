package ru.covariance.optimizationmethods.core.methods.four;

import ru.covariance.optimizationmethods.core.Matrix;
import ru.covariance.optimizationmethods.core.Point;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public abstract class AbstractMultidimMinimizer {
    public static double epsilon = 1e-2;

    public Point x;
    protected final ToDoubleFunction<Point> f;
    protected final UnaryOperator<Point> grad;
    protected final Function<Point, Matrix> gessian;

    protected AbstractMultidimMinimizer(final ToDoubleFunction<Point> f,
                                        final UnaryOperator<Point> grad,
                                        final Function<Point, Matrix> gessian,
                                        final Point x0) {
        this.f = f;
        this.grad = grad;
        this.gessian = gessian;
        x = x0;
    }

    public abstract void iterate();

    public abstract void print();

    public abstract boolean converged();

    public int test() {
        int iteration = 0;
        do {
            ++iteration;
            iterate();
            print();
        } while (!converged());
//        System.out.println("\\hline");
//        System.out.println("\\end{tabular}");
        return iteration;
    }
}
