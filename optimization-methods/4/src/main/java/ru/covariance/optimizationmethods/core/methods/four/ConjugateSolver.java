package ru.covariance.optimizationmethods.core.methods.four;

import ru.covariance.optimizationmethods.core.Matrix;
import ru.covariance.optimizationmethods.core.Point;

public class ConjugateSolver {
    public static Point solveSOLE(final Matrix a, final Point f, final double eps) {
        Point x = f;
        Point r = f.subtract(a.multiply(x));
        Point z = r;
        while (r.magnitude() / f.magnitude() >= eps) {
            double rDot = r.dotProduct(r);
            double ak = rDot / a.multiply(z).dotProduct(z);
            x = x.add(z.multiply(ak));
            final Point r1 = r.subtract(a.multiply(z).multiply(ak));
            double bk = r1.dotProduct(r1) / rDot;
            z = r1.add(z.multiply(bk));
            r = r1;
        }
        return x;
    }
}
