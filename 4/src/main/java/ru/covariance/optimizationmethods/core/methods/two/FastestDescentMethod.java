package ru.covariance.optimizationmethods.core.methods.two;

import ru.covariance.optimizationmethods.core.Point;
import ru.covariance.optimizationmethods.core.methods.one.GoldenRatioMinimizer;

import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

public class FastestDescentMethod {
    private final ToDoubleFunction<Point> f;
    private final UnaryOperator<Point> gradient;
    private Point curPoint;
    private Point curDirection;
    private Point prevPoint;

    public FastestDescentMethod(Point x0, ToDoubleFunction<Point> f, UnaryOperator<Point> gradient) {
        this.f = f;
        this.gradient = gradient;
        this.prevPoint = this.curPoint = x0;
        curDirection = gradient.apply(curPoint).multiply(-1);
    }

    public void iterate() {
        double alpha = new GoldenRatioMinimizer(0, 10, t -> f.applyAsDouble(curPoint.add(curDirection.multiply(t)))).getMin();
        assert f.applyAsDouble(curPoint) > f.applyAsDouble(curPoint.add(curDirection.multiply(alpha)));
        prevPoint = curPoint;
        curPoint = curPoint.add(curDirection.multiply(alpha));
        curDirection = gradient.apply(curPoint).multiply(-1);
    }

    public Point getMin() {
        while (!converged()) {
            iterate();
        }
        return curPoint;
    }

    public int test() {
        int iteration = 0;
        while (!converged()) {
            ++iteration;
            iterate();
            System.out.printf("B((%s), (%s), H)%n", prevPoint.toString(), curPoint.toString());
        }
        return iteration - 1;
    }

    public boolean converged() {
        return curDirection.magnitude() < 1e-2;
    }
}
